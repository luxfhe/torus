// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Bufferization/IR/BufferizableOpInterface.h"
#include "mlir/Dialect/Bufferization/Transforms/BufferUtils.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/IR/Dialect.h"
#include "mlir/IR/Operation.h"

#include "toruslang/Conversion/Tools.h"
#include "toruslang/Dialect/Torus/IR/TorusDialect.h"
#include "toruslang/Dialect/Torus/IR/TorusOps.h"
#include "toruslang/Dialect/Torus/Transforms/BufferizableOpInterfaceImpl.h"
#include "toruslang/Dialect/Tracing/IR/TracingOps.h"
#include "toruslang/Support/CompilerEngine.h"
#include <mlir/IR/AffineExpr.h>
#include <mlir/IR/AffineMap.h>
#include <mlir/IR/BuiltinTypes.h>

using namespace mlir;
using namespace mlir::bufferization;
using namespace mlir::tensor;

namespace {

namespace Tracing = mlir::toruslang::Tracing;
namespace Torus = mlir::toruslang::Torus;

template <typename TensorOp, typename MemrefOp>
struct TensorToMemrefOp : public BufferizableOpInterface::ExternalModel<
                              TensorToMemrefOp<TensorOp, MemrefOp>, TensorOp> {
  bool bufferizesToMemoryRead(Operation *op, OpOperand &opOperand,
                              const AnalysisState &state) const {
    return true;
  }

  bool bufferizesToMemoryWrite(Operation *op, OpOperand &opOperand,
                               const AnalysisState &state) const {
    return false;
  }

  AliasingOpResultList getAliasingOpResults(Operation *op, OpOperand &opOperand,
                                            const AnalysisState &state) const {
    return {};
  }

  BufferRelation bufferRelation(Operation *op, OpResult opResult,
                                const AnalysisState &state) const {
    return BufferRelation::Unknown;
  }

  LogicalResult bufferize(Operation *op, RewriterBase &rewriter,
                          const BufferizationOptions &options) const {

    auto loc = op->getLoc();
    auto castOp = cast<TensorOp>(op);

    auto resTensorType =
        castOp.getResult().getType().template cast<mlir::TensorType>();

    auto outMemrefType = MemRefType::get(resTensorType.getShape(),
                                         resTensorType.getElementType());
    auto outMemref = options.createAlloc(rewriter, loc, outMemrefType, {});
    if (mlir::failed(outMemref)) {
      return mlir::failure();
    }

    // The first operand is the result
    mlir::SmallVector<mlir::Value, 3> operands{
        *outMemref,
    };
    for (auto &operand : op->getOpOperands()) {
      if (!operand.get().getType().isa<mlir::RankedTensorType>()) {
        operands.push_back(operand.get());
      } else {
        operands.push_back(
            *bufferization::getBuffer(rewriter, operand.get(), options));
      }
    }

    rewriter.create<MemrefOp>(loc, mlir::TypeRange{}, operands, op->getAttrs());

    replaceOpWithBufferizedValues(rewriter, op, *outMemref);

    return success();
  }
};

} // namespace

void mlir::toruslang::Torus::
    registerBufferizableOpInterfaceExternalModels(DialectRegistry &registry) {
  registry.addExtension(+[](MLIRContext *ctx,
                            Torus::TorusDialect *dialect) {
    // add_lwe_tensor => add_lwe_buffer
    Torus::AddLweTensorOp::attachInterface<
        TensorToMemrefOp<Torus::AddLweTensorOp, Torus::AddLweBufferOp>>(
        *ctx);
    // add_plaintext_lwe_tensor => add_plaintext_lwe_buffer
    Torus::AddPlaintextLweTensorOp::attachInterface<TensorToMemrefOp<
        Torus::AddPlaintextLweTensorOp, Torus::AddPlaintextLweBufferOp>>(
        *ctx);
    // mul_cleartext_lwe_tensor => mul_cleartext_lwe_buffer
    Torus::MulCleartextLweTensorOp::attachInterface<TensorToMemrefOp<
        Torus::MulCleartextLweTensorOp, Torus::MulCleartextLweBufferOp>>(
        *ctx);
    // negate_cleartext_lwe_tensor => negate_cleartext_lwe_buffer
    Torus::NegateLweTensorOp::attachInterface<TensorToMemrefOp<
        Torus::NegateLweTensorOp, Torus::NegateLweBufferOp>>(*ctx);
    // negate_cleartext_lwe_tensor => negate_cleartext_lwe_buffer
    Torus::NegateLweTensorOp::attachInterface<TensorToMemrefOp<
        Torus::NegateLweTensorOp, Torus::NegateLweBufferOp>>(*ctx);
    // keyswitch_lwe_tensor => keyswitch_lwe_buffer
    Torus::KeySwitchLweTensorOp::attachInterface<TensorToMemrefOp<
        Torus::KeySwitchLweTensorOp, Torus::KeySwitchLweBufferOp>>(*ctx);
    // bootstrap_lwe_tensor => bootstrap_lwe_buffer
    Torus::BootstrapLweTensorOp::attachInterface<TensorToMemrefOp<
        Torus::BootstrapLweTensorOp, Torus::BootstrapLweBufferOp>>(*ctx);

    // batched_add_lwe_tensor => batched_add_lwe_buffer
    Torus::BatchedAddLweTensorOp::attachInterface<TensorToMemrefOp<
        Torus::BatchedAddLweTensorOp, Torus::BatchedAddLweBufferOp>>(
        *ctx);
    // batched_add_plaintext_lwe_tensor => batched_add_plaintext_lwe_buffer
    Torus::BatchedAddPlaintextLweTensorOp::attachInterface<
        TensorToMemrefOp<Torus::BatchedAddPlaintextLweTensorOp,
                         Torus::BatchedAddPlaintextLweBufferOp>>(*ctx);
    // batched_add_plaintext_cst_lwe_tensor =>
    // batched_add_plaintext_cst_lwe_buffer
    Torus::BatchedAddPlaintextCstLweTensorOp::attachInterface<
        TensorToMemrefOp<Torus::BatchedAddPlaintextCstLweTensorOp,
                         Torus::BatchedAddPlaintextCstLweBufferOp>>(*ctx);
    // batched_mul_cleartext_lwe_tensor => batched_mul_cleartext_lwe_buffer
    Torus::BatchedMulCleartextLweTensorOp::attachInterface<
        TensorToMemrefOp<Torus::BatchedMulCleartextLweTensorOp,
                         Torus::BatchedMulCleartextLweBufferOp>>(*ctx);
    // batched_mul_cleartext_cst_lwe_tensor =>
    // batched_mul_cleartext_cst_lwe_buffer
    Torus::BatchedMulCleartextCstLweTensorOp::attachInterface<
        TensorToMemrefOp<Torus::BatchedMulCleartextCstLweTensorOp,
                         Torus::BatchedMulCleartextCstLweBufferOp>>(*ctx);
    // batched_negate_lwe_tensor => batched_negate_lwe_buffer
    Torus::BatchedNegateLweTensorOp::attachInterface<
        TensorToMemrefOp<Torus::BatchedNegateLweTensorOp,
                         Torus::BatchedNegateLweBufferOp>>(*ctx);

    // batched_keyswitch_lwe_tensor => batched_keyswitch_lwe_buffer
    Torus::BatchedKeySwitchLweTensorOp::attachInterface<
        TensorToMemrefOp<Torus::BatchedKeySwitchLweTensorOp,
                         Torus::BatchedKeySwitchLweBufferOp>>(*ctx);
    // batched_bootstrap_lwe_tensor => batched_bootstrap_lwe_buffer
    Torus::BatchedBootstrapLweTensorOp::attachInterface<
        TensorToMemrefOp<Torus::BatchedBootstrapLweTensorOp,
                         Torus::BatchedBootstrapLweBufferOp>>(*ctx);
    // batched_mapped_bootstrap_lwe_tensor =>
    // batched_mapped_bootstrap_lwe_buffer
    Torus::BatchedMappedBootstrapLweTensorOp::attachInterface<
        TensorToMemrefOp<Torus::BatchedMappedBootstrapLweTensorOp,
                         Torus::BatchedMappedBootstrapLweBufferOp>>(*ctx);
    // wop_pbs_crt_lwe_tensor => wop_pbs_crt_lwe_buffer
    Torus::WopPBSCRTLweTensorOp::attachInterface<TensorToMemrefOp<
        Torus::WopPBSCRTLweTensorOp, Torus::WopPBSCRTLweBufferOp>>(*ctx);
    // encode_plaintext_with_crt_tensor => encode_plaintext_with_crt_buffer
    Torus::EncodePlaintextWithCrtTensorOp::attachInterface<
        TensorToMemrefOp<Torus::EncodePlaintextWithCrtTensorOp,
                         Torus::EncodePlaintextWithCrtBufferOp>>(*ctx);
    // encode_expand_lut_for_bootstrap_tensor =>
    // encode_expand_lut_for_bootstrap_buffer
    Torus::EncodeExpandLutForBootstrapTensorOp::attachInterface<
        TensorToMemrefOp<Torus::EncodeExpandLutForBootstrapTensorOp,
                         Torus::EncodeExpandLutForBootstrapBufferOp>>(*ctx);
    // encode_lut_for_crt_woppbs_tensor =>
    // encode_lut_for_crt_woppbs_buffer
    Torus::EncodeLutForCrtWopPBSTensorOp::attachInterface<
        TensorToMemrefOp<Torus::EncodeLutForCrtWopPBSTensorOp,
                         Torus::EncodeLutForCrtWopPBSBufferOp>>(*ctx);
  });
}
