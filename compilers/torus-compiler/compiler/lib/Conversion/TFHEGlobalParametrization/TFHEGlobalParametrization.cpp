// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/DialectConversion.h"

#include "toruslang/Conversion/Passes.h"
#include "toruslang/Conversion/Utils/FuncConstOpConversion.h"
#include "toruslang/Conversion/Utils/GenericOpTypeConversionPattern.h"
#include "toruslang/Conversion/Utils/RTOpConverter.h"
#include "toruslang/Conversion/Utils/RegionOpTypeConverterPattern.h"
#include "toruslang/Conversion/Utils/TensorOpTypeConversion.h"
#include "toruslang/Dialect/RT/IR/RTOps.h"
#include "toruslang/Dialect/TFHE/IR/TFHEDialect.h"
#include "toruslang/Dialect/TFHE/IR/TFHEOps.h"
#include "toruslang/Dialect/TFHE/IR/TFHETypes.h"
#include "toruslang/Dialect/Tracing/IR/TracingOps.h"
#include "toruslang/Support/Constants.h"
#include <mlir/Dialect/Bufferization/IR/Bufferization.h>

namespace TFHE = mlir::toruslang::TFHE;

namespace {
struct TFHEGlobalParametrizationPass
    : public TFHEGlobalParametrizationBase<TFHEGlobalParametrizationPass> {
  TFHEGlobalParametrizationPass(
      const mlir::toruslang::V0Parameter cryptoParameters)
      : cryptoParameters(cryptoParameters){};
  void runOnOperation() final;
  const mlir::toruslang::V0Parameter cryptoParameters;
};
} // namespace

using mlir::toruslang::TFHE::GLWECipherTextType;

/// TFHEGlobalParametrizationTypeConverter is a TypeConverter that transform
/// `TFHE.glwe<sk?>` to
/// `TFHE.glwe<sk[id]<glweDimension,polynomialSize>>`
class TFHEGlobalParametrizationTypeConverter : public mlir::TypeConverter {

public:
  TFHEGlobalParametrizationTypeConverter(
      const mlir::toruslang::V0Parameter cryptoParameters)
      : cryptoParameters(cryptoParameters) {
    addConversion([](mlir::Type type) { return type; });
    addConversion([&](GLWECipherTextType type) {
      if (type.getKey().isNone()) {
        return this->glweInterPBSType(type);
      } else {
        return type;
      }
    });
    addConversion([&](mlir::RankedTensorType type) {
      return mlir::RankedTensorType::get(
          type.getShape(), this->convertType(type.getElementType()));
    });
    addConversion([&](mlir::toruslang::RT::FutureType type) {
      return mlir::toruslang::RT::FutureType::get(
          this->convertType(type.dyn_cast<mlir::toruslang::RT::FutureType>()
                                .getElementType()));
    });
    addConversion([&](mlir::toruslang::RT::PointerType type) {
      return mlir::toruslang::RT::PointerType::get(
          this->convertType(type.dyn_cast<mlir::toruslang::RT::PointerType>()
                                .getElementType()));
    });
  }

  TFHE::GLWESecretKey getInterPBSKey() {
    auto dimension = cryptoParameters.getNBigLweDimension();
    auto polynomialSize = 1;
    auto identifier = 0;
    return mlir::toruslang::TFHE::GLWESecretKey::newParameterized(
        dimension, polynomialSize, identifier);
  }

  TFHE::GLWECipherTextType glweInterPBSType(GLWECipherTextType &type) {
    return TFHE::GLWECipherTextType::get(type.getContext(), getInterPBSKey());
  }

  TFHE::GLWESecretKey getIntraPBSKey() {
    auto dimension = cryptoParameters.nSmall;
    auto polynomialSize = 1;
    auto identifier = 1;
    return mlir::toruslang::TFHE::GLWESecretKey::newParameterized(
        dimension, polynomialSize, identifier);
  }

  TFHE::GLWECipherTextType glweIntraPBSType(GLWECipherTextType &type) {
    return TFHE::GLWECipherTextType::get(type.getContext(), getIntraPBSKey());
  }

  const mlir::toruslang::V0Parameter cryptoParameters;
};

struct KeySwitchGLWEOpPattern
    : public mlir::OpRewritePattern<TFHE::KeySwitchGLWEOp> {
  KeySwitchGLWEOpPattern(mlir::MLIRContext *context,
                         TFHEGlobalParametrizationTypeConverter &converter,
                         const mlir::toruslang::V0Parameter cryptoParameters,
                         mlir::PatternBenefit benefit =
                             mlir::toruslang::DEFAULT_PATTERN_BENEFIT)
      : mlir::OpRewritePattern<TFHE::KeySwitchGLWEOp>(context, benefit),
        converter(converter), cryptoParameters(cryptoParameters) {}

  mlir::LogicalResult
  matchAndRewrite(TFHE::KeySwitchGLWEOp ksOp,
                  mlir::PatternRewriter &rewriter) const override {
    auto inputTy =
        ksOp.getCiphertext().getType().cast<TFHE::GLWECipherTextType>();
    auto newInputTy = converter.convertType(inputTy)
                          .cast<mlir::toruslang::TFHE::GLWECipherTextType>();
    auto outputTy = ksOp.getResult().getType().cast<TFHE::GLWECipherTextType>();
    auto newOutputTy = converter.glweIntraPBSType(outputTy);
    auto newInputKey = converter.getInterPBSKey();
    auto newOutputKey = converter.getIntraPBSKey();
    auto keyswitchKey = TFHE::GLWEKeyswitchKeyAttr::get(
        ksOp->getContext(), newInputKey, newOutputKey, cryptoParameters.ksLevel,
        cryptoParameters.ksLogBase, -1);
    auto newOp = rewriter.replaceOpWithNewOp<TFHE::KeySwitchGLWEOp>(
        ksOp, newOutputTy, ksOp.getCiphertext(), keyswitchKey);
    rewriter.startRootUpdate(newOp);
    newOp.getCiphertext().setType(newInputTy);
    rewriter.finalizeRootUpdate(newOp);
    return mlir::success();
  };

private:
  TFHEGlobalParametrizationTypeConverter &converter;
  const mlir::toruslang::V0Parameter cryptoParameters;
};

struct BootstrapGLWEOpPattern
    : public mlir::OpRewritePattern<TFHE::BootstrapGLWEOp> {
  BootstrapGLWEOpPattern(mlir::MLIRContext *context,
                         TFHEGlobalParametrizationTypeConverter &converter,
                         const mlir::toruslang::V0Parameter cryptoParameters,
                         mlir::PatternBenefit benefit =
                             mlir::toruslang::DEFAULT_PATTERN_BENEFIT)
      : mlir::OpRewritePattern<TFHE::BootstrapGLWEOp>(context, benefit),
        converter(converter), cryptoParameters(cryptoParameters) {}

  mlir::LogicalResult
  matchAndRewrite(TFHE::BootstrapGLWEOp bsOp,
                  mlir::PatternRewriter &rewriter) const override {
    auto inputTy =
        bsOp.getCiphertext().getType().cast<TFHE::GLWECipherTextType>();
    auto newInputTy = converter.glweIntraPBSType(inputTy);
    auto outputTy = bsOp.getResult().getType().cast<TFHE::GLWECipherTextType>();
    auto newOutputTy =
        converter.convertType(outputTy).cast<TFHE::GLWECipherTextType>();
    auto newInputKey = converter.getIntraPBSKey();
    auto newOutputKey = converter.getInterPBSKey();
    auto bootstrapKey = TFHE::GLWEBootstrapKeyAttr::get(
        bsOp->getContext(), newInputKey, newOutputKey,
        cryptoParameters.getPolynomialSize(), cryptoParameters.glweDimension,
        cryptoParameters.brLevel, cryptoParameters.brLogBase, -1);
    auto newOp = rewriter.replaceOpWithNewOp<TFHE::BootstrapGLWEOp>(
        bsOp, newOutputTy, bsOp.getCiphertext(), bsOp.getLookupTable(),
        bootstrapKey);
    rewriter.startRootUpdate(newOp);
    newOp.getCiphertext().setType(newInputTy);
    rewriter.finalizeRootUpdate(newOp);
    return mlir::success();
  };

private:
  TFHEGlobalParametrizationTypeConverter &converter;
  const mlir::toruslang::V0Parameter cryptoParameters;
};

struct WopPBSGLWEOpPattern : public mlir::OpRewritePattern<TFHE::WopPBSGLWEOp> {
  WopPBSGLWEOpPattern(mlir::MLIRContext *context,
                      TFHEGlobalParametrizationTypeConverter &converter,
                      const mlir::toruslang::V0Parameter cryptoParameters,
                      mlir::PatternBenefit benefit =
                          mlir::toruslang::DEFAULT_PATTERN_BENEFIT)
      : mlir::OpRewritePattern<TFHE::WopPBSGLWEOp>(context, benefit),
        converter(converter), cryptoParameters(cryptoParameters) {}

  mlir::LogicalResult
  matchAndRewrite(TFHE::WopPBSGLWEOp wopPBSOp,
                  mlir::PatternRewriter &rewriter) const override {
    auto inputTy =
        wopPBSOp.getCiphertexts().getType().cast<mlir::RankedTensorType>();
    auto newInputTy =
        converter.convertType(inputTy).cast<mlir::RankedTensorType>();
    auto outputTy = wopPBSOp.getType().cast<mlir::RankedTensorType>();
    auto newOutputType = converter.convertType(outputTy);
    auto interKey = converter.getInterPBSKey();
    auto intraKey = converter.getIntraPBSKey();
    auto keyswitchKey = TFHE::GLWEKeyswitchKeyAttr::get(
        wopPBSOp->getContext(), interKey, intraKey, cryptoParameters.ksLevel,
        cryptoParameters.ksLogBase, -1);
    auto bootstrapKey = TFHE::GLWEBootstrapKeyAttr::get(
        wopPBSOp->getContext(), intraKey, interKey,
        cryptoParameters.getPolynomialSize(), cryptoParameters.glweDimension,
        cryptoParameters.brLevel, cryptoParameters.brLogBase, -1);
    auto packingKeyswitchKey = TFHE::GLWEPackingKeyswitchKeyAttr::get(
        wopPBSOp->getContext(), interKey, interKey,
        cryptoParameters.largeInteger->wopPBS.packingKeySwitch
            .outputPolynomialSize,
        cryptoParameters.largeInteger->wopPBS.packingKeySwitch
            .inputLweDimension,
        cryptoParameters.glweDimension,
        cryptoParameters.largeInteger->wopPBS.packingKeySwitch.level,
        cryptoParameters.largeInteger->wopPBS.packingKeySwitch.baseLog, -1);
    auto newOp = rewriter.replaceOpWithNewOp<TFHE::WopPBSGLWEOp>(
        wopPBSOp, newOutputType, wopPBSOp.getCiphertexts(),
        wopPBSOp.getLookupTable(), keyswitchKey, bootstrapKey,
        packingKeyswitchKey,
        rewriter.getI64ArrayAttr(
            cryptoParameters.largeInteger->crtDecomposition),
        rewriter.getI32IntegerAttr(
            cryptoParameters.largeInteger->wopPBS.circuitBootstrap.level),
        rewriter.getI32IntegerAttr(
            cryptoParameters.largeInteger->wopPBS.circuitBootstrap.baseLog));
    rewriter.startRootUpdate(newOp);
    newOp.getCiphertexts().setType(newInputTy);
    rewriter.finalizeRootUpdate(newOp);
    return mlir::success();
  };

private:
  TFHEGlobalParametrizationTypeConverter &converter;
  const mlir::toruslang::V0Parameter cryptoParameters;
};

template <typename Op>
void populateWithTFHEOpTypeConversionPattern(
    mlir::RewritePatternSet &patterns, mlir::ConversionTarget &target,
    mlir::TypeConverter &typeConverter) {
  patterns.add<mlir::toruslang::GenericTypeConverterPattern<Op>>(
      patterns.getContext(), typeConverter);

  target.addDynamicallyLegalOp<Op>(
      [&](Op op) { return typeConverter.isLegal(op->getResultTypes()); });
}

/// Populate the RewritePatternSet with all patterns that rewrite Torus
/// operators to the corresponding function call to the `Torus C API`.
void populateWithTFHEOpTypeConversionPatterns(
    mlir::RewritePatternSet &patterns, mlir::ConversionTarget &target,
    mlir::TypeConverter &typeConverter) {
  populateWithTFHEOpTypeConversionPattern<mlir::toruslang::TFHE::ZeroGLWEOp>(
      patterns, target, typeConverter);
  populateWithTFHEOpTypeConversionPattern<
      mlir::toruslang::TFHE::ZeroTensorGLWEOp>(patterns, target,
                                                  typeConverter);
  populateWithTFHEOpTypeConversionPattern<
      mlir::toruslang::TFHE::AddGLWEIntOp>(patterns, target, typeConverter);
  populateWithTFHEOpTypeConversionPattern<mlir::toruslang::TFHE::AddGLWEOp>(
      patterns, target, typeConverter);
  populateWithTFHEOpTypeConversionPattern<
      mlir::toruslang::TFHE::SubGLWEIntOp>(patterns, target, typeConverter);
  populateWithTFHEOpTypeConversionPattern<mlir::toruslang::TFHE::NegGLWEOp>(
      patterns, target, typeConverter);
  populateWithTFHEOpTypeConversionPattern<
      mlir::toruslang::TFHE::MulGLWEIntOp>(patterns, target, typeConverter);
}

void TFHEGlobalParametrizationPass::runOnOperation() {
  auto op = this->getOperation();

  TFHEGlobalParametrizationTypeConverter converter(cryptoParameters);

  // Parametrize
  {
    mlir::ConversionTarget target(getContext());
    mlir::RewritePatternSet patterns(&getContext());

    // function signature
    target.addDynamicallyLegalOp<mlir::func::FuncOp>(
        [&](mlir::func::FuncOp funcOp) {
          return converter.isSignatureLegal(funcOp.getFunctionType()) &&
                 converter.isLegal(&funcOp.getBody());
        });
    target.addDynamicallyLegalOp<mlir::func::ConstantOp>(
        [&](mlir::func::ConstantOp op) {
          return FunctionConstantOpConversion<
              TFHEGlobalParametrizationTypeConverter>::isLegal(op, converter);
        });
    patterns.add<
        FunctionConstantOpConversion<TFHEGlobalParametrizationTypeConverter>>(
        &getContext(), converter);
    mlir::populateFunctionOpInterfaceTypeConversionPattern<mlir::func::FuncOp>(
        patterns, converter);

    // Parametrize keyswitch
    target.addLegalOp<mlir::arith::ConstantOp>();
    patterns.add<KeySwitchGLWEOpPattern>(&getContext(), converter,
                                         cryptoParameters);
    target.addDynamicallyLegalOp<TFHE::KeySwitchGLWEOp>(
        [&](TFHE::KeySwitchGLWEOp op) {
          return op.getKeyAttr().getInputKey().isParameterized() &&
                 op.getKeyAttr().getOutputKey().isParameterized() &&
                 op.getKeyAttr().getBaseLog() != -1 &&
                 op.getKeyAttr().getLevels() != -1;
        });

    // Parametrize bootstrap
    patterns.add<BootstrapGLWEOpPattern>(&getContext(), converter,
                                         cryptoParameters);
    target.addDynamicallyLegalOp<TFHE::BootstrapGLWEOp>(
        [&](TFHE::BootstrapGLWEOp op) {
          return op.getKeyAttr().getInputKey().isParameterized() &&
                 op.getKeyAttr().getOutputKey().isParameterized() &&
                 op.getKeyAttr().getLevels() != -1 &&
                 op.getKeyAttr().getBaseLog() != -1 &&
                 op.getKeyAttr().getGlweDim() != -1 &&
                 op.getKeyAttr().getPolySize() != -1;
        });

    // Parametrize wop pbs
    patterns.add<WopPBSGLWEOpPattern>(&getContext(), converter,
                                      cryptoParameters);
    target.addDynamicallyLegalOp<TFHE::WopPBSGLWEOp>(
        [&](TFHE::WopPBSGLWEOp op) {
          return op.getKskAttr().getInputKey().isParameterized() &&
                 op.getKskAttr().getOutputKey().isParameterized() &&
                 op.getKskAttr().getBaseLog() != -1 &&
                 op.getKskAttr().getLevels() != -1 &&
                 op.getBskAttr().getInputKey().isParameterized() &&
                 op.getBskAttr().getOutputKey().isParameterized() &&
                 op.getBskAttr().getLevels() != -1 &&
                 op.getBskAttr().getBaseLog() != -1 &&
                 op.getBskAttr().getGlweDim() != -1 &&
                 op.getBskAttr().getPolySize() != -1 &&
                 op.getPkskAttr().getInputKey().isParameterized() &&
                 op.getPkskAttr().getOutputKey().isParameterized() &&
                 op.getPkskAttr().getLevels() != -1 &&
                 op.getPkskAttr().getBaseLog() != -1;
        });

    // Add all patterns to convert TFHE types
    populateWithTFHEOpTypeConversionPatterns(patterns, target, converter);

    patterns.add<mlir::toruslang::GenericTypeConverterPattern<
        mlir::bufferization::AllocTensorOp>>(&getContext(), converter);
    mlir::toruslang::addDynamicallyLegalTypeOp<
        mlir::bufferization::AllocTensorOp>(target, converter);

    patterns.add<
        mlir::toruslang::GenericTypeConverterPattern<mlir::tensor::EmptyOp>>(
        &getContext(), converter);
    mlir::toruslang::addDynamicallyLegalTypeOp<mlir::tensor::EmptyOp>(
        target, converter);

    patterns.add<
        mlir::toruslang::GenericTypeConverterPattern<mlir::tensor::DimOp>>(
        &getContext(), converter);
    mlir::toruslang::addDynamicallyLegalTypeOp<mlir::tensor::DimOp>(
        target, converter);

    patterns.add<mlir::toruslang::GenericTypeConverterPattern<
        mlir::tensor::FromElementsOp>>(&getContext(), converter);
    mlir::toruslang::addDynamicallyLegalTypeOp<mlir::tensor::FromElementsOp>(
        target, converter);

    patterns.add<RegionOpTypeConverterPattern<
        mlir::scf::InParallelOp, TFHEGlobalParametrizationTypeConverter>>(
        &getContext(), converter);
    patterns.add<RegionOpTypeConverterPattern<
        mlir::linalg::GenericOp, TFHEGlobalParametrizationTypeConverter>>(
        &getContext(), converter);
    patterns.add<RegionOpTypeConverterPattern<
        mlir::tensor::GenerateOp, TFHEGlobalParametrizationTypeConverter>>(
        &getContext(), converter);
    patterns.add<RegionOpTypeConverterPattern<
        mlir::scf::ForOp, TFHEGlobalParametrizationTypeConverter>>(
        &getContext(), converter);
    patterns.add<RegionOpTypeConverterPattern<
        mlir::scf::ForallOp, TFHEGlobalParametrizationTypeConverter>>(
        &getContext(), converter);
    patterns.add<RegionOpTypeConverterPattern<
        mlir::func::ReturnOp, TFHEGlobalParametrizationTypeConverter>>(
        &getContext(), converter);
    mlir::toruslang::addDynamicallyLegalTypeOp<mlir::func::ReturnOp>(
        target, converter);
    patterns.add<RegionOpTypeConverterPattern<
        mlir::linalg::YieldOp, TFHEGlobalParametrizationTypeConverter>>(
        &getContext(), converter);
    mlir::toruslang::addDynamicallyLegalTypeOp<mlir::linalg::YieldOp>(
        target, converter);
    mlir::toruslang::addDynamicallyLegalTypeOp<
        mlir::tensor::ParallelInsertSliceOp>(target, converter);

    mlir::toruslang::populateWithTensorTypeConverterPatterns(
        patterns, target, converter);

    mlir::toruslang::addDynamicallyLegalTypeOp<
        mlir::toruslang::Tracing::TraceCiphertextOp>(target, converter);

    patterns.add<
        mlir::toruslang::GenericTypeConverterPattern<
            mlir::toruslang::Tracing::TraceCiphertextOp>,
        mlir::toruslang::GenericTypeConverterPattern<mlir::func::ReturnOp>,
        mlir::toruslang::GenericTypeConverterPattern<mlir::scf::YieldOp>,
        mlir::toruslang::GenericTypeConverterPattern<
            mlir::tensor::ParallelInsertSliceOp>>(&getContext(), converter);

    mlir::toruslang::populateWithRTTypeConverterPatterns(patterns, target,
                                                            converter);

    // Apply conversion
    if (mlir::applyPartialConversion(op, target, std::move(patterns))
            .failed()) {
      this->signalPassFailure();
    }
  }
}

namespace mlir {
namespace toruslang {
std::unique_ptr<OperationPass<ModuleOp>>
createConvertTFHEGlobalParametrizationPass(const V0Parameter parameter) {
  return std::make_unique<TFHEGlobalParametrizationPass>(parameter);
}
} // namespace toruslang
} // namespace mlir
