// Part of the Concrete Compiler Project, under the BSD3 License with Zama
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "toruslang/Dialect/Tracing/IR/TracingOps.h"
#include <mlir/Dialect/Arith/IR/Arith.h>
#include <mlir/IR/PatternMatch.h>
#include <mlir/Transforms/GreedyPatternRewriteDriver.h>

#include <toruslang/Dialect/FHE/IR/FHEOps.h>
#include <toruslang/Dialect/FHE/IR/FHETypes.h>
#include <toruslang/Dialect/FHE/Transforms/Boolean/Boolean.h>
#include <toruslang/Support/Constants.h>

namespace mlir {
namespace toruslang {

namespace {

/// Rewrite an `FHE.gen_gate` operation as an LUT operation by composing a
/// single index from the two boolean inputs.
class GenGatePattern
    : public mlir::OpRewritePattern<mlir::toruslang::FHE::GenGateOp> {
public:
  GenGatePattern(mlir::MLIRContext *context)
      : mlir::OpRewritePattern<mlir::toruslang::FHE::GenGateOp>(
            context, ::mlir::toruslang::DEFAULT_PATTERN_BENEFIT) {}

  mlir::LogicalResult
  matchAndRewrite(mlir::toruslang::FHE::GenGateOp op,
                  mlir::PatternRewriter &rewriter) const override {
    auto eint2 = mlir::toruslang::FHE::EncryptedUnsignedIntegerType::get(
        rewriter.getContext(), 2);
    auto left = rewriter
                    .create<mlir::toruslang::FHE::FromBoolOp>(
                        op.getLoc(), eint2, op.getLeft())
                    .getResult();
    auto right = rewriter
                     .create<mlir::toruslang::FHE::FromBoolOp>(
                         op.getLoc(), eint2, op.getRight())
                     .getResult();
    auto cst_two =
        rewriter.create<mlir::arith::ConstantIntOp>(op.getLoc(), 2, 3)
            .getResult();
    auto leftMulTwo = rewriter
                          .create<mlir::toruslang::FHE::MulEintIntOp>(
                              op.getLoc(), left, cst_two)
                          .getResult();
    auto newIndex = rewriter
                        .create<mlir::toruslang::FHE::AddEintOp>(
                            op.getLoc(), leftMulTwo, right)
                        .getResult();
    auto lut_result =
        rewriter.create<mlir::toruslang::FHE::ApplyLookupTableEintOp>(
            op.getLoc(), eint2, newIndex, op.getTruthTable());
    rewriter.replaceOpWithNewOp<mlir::toruslang::FHE::ToBoolOp>(
        op,
        mlir::toruslang::FHE::EncryptedBooleanType::get(
            rewriter.getContext()),
        lut_result);
    return mlir::success();
  }
};

/// Rewrite an FHE GateOp (e.g. And/Or) into a GenGate with the given truth
/// table.
template <typename GateOp>
class GeneralizeGatePattern : public mlir::OpRewritePattern<GateOp> {
public:
  GeneralizeGatePattern(mlir::MLIRContext *context,
                        llvm::SmallVector<uint64_t, 4> truth_table_vector)
      : mlir::OpRewritePattern<GateOp>(
            context, ::mlir::toruslang::DEFAULT_PATTERN_BENEFIT),
        truth_table_vector(truth_table_vector) {}

  mlir::LogicalResult
  matchAndRewrite(GateOp op, mlir::PatternRewriter &rewriter) const override {
    auto truth_table_attr = mlir::DenseElementsAttr::get(
        mlir::RankedTensorType::get({4}, rewriter.getIntegerType(64)),
        {llvm::APInt(1, this->truth_table_vector[0], false),
         llvm::APInt(1, this->truth_table_vector[1], false),
         llvm::APInt(1, this->truth_table_vector[2], false),
         llvm::APInt(1, this->truth_table_vector[3], false)});
    auto truth_table =
        rewriter.create<mlir::arith::ConstantOp>(op.getLoc(), truth_table_attr);
    rewriter.replaceOpWithNewOp<mlir::toruslang::FHE::GenGateOp>(
        op, op.getResult().getType(), op.getLeft(), op.getRight(), truth_table);
    return mlir::success();
  }

private:
  llvm::SmallVector<uint64_t, 4> truth_table_vector;
};

/// Rewrite an `FHE.mux` op, into a series of boolean and arithmetic operations
/// mux(cond, c1, c2) => c1 and not cond + c2 and cond
class MuxOpPattern
    : public mlir::OpRewritePattern<mlir::toruslang::FHE::MuxOp> {
public:
  MuxOpPattern(mlir::MLIRContext *context)
      : mlir::OpRewritePattern<mlir::toruslang::FHE::MuxOp>(
            context, ::mlir::toruslang::DEFAULT_PATTERN_BENEFIT) {}

  mlir::LogicalResult
  matchAndRewrite(mlir::toruslang::FHE::MuxOp op,
                  mlir::PatternRewriter &rewriter) const override {
    auto eint2 = mlir::toruslang::FHE::EncryptedUnsignedIntegerType::get(
        rewriter.getContext(), 2);
    auto boolType = mlir::toruslang::FHE::EncryptedBooleanType::get(
        rewriter.getContext());

    // truth table for c1 and not cond
    auto truth_table_attr = mlir::DenseElementsAttr::get(
        mlir::RankedTensorType::get({4}, rewriter.getIntegerType(64)),
        {llvm::APInt(1, 0, false), llvm::APInt(1, 0, false),
         llvm::APInt(1, 1, false), llvm::APInt(1, 0, false)});
    auto truth_table =
        rewriter.create<mlir::arith::ConstantOp>(op.getLoc(), truth_table_attr);
    auto c1AndNotCond =
        rewriter
            .create<mlir::toruslang::FHE::GenGateOp>(
                op.getLoc(), boolType, op.getC1(), op.getCond(), truth_table)
            .getResult();
    auto c2AndCond = rewriter
                         .create<mlir::toruslang::FHE::BoolAndOp>(
                             op.getLoc(), boolType, op.getC2(), op.getCond())
                         .getResult();

    auto c1AndNotCondBool = rewriter
                                .create<mlir::toruslang::FHE::FromBoolOp>(
                                    op.getLoc(), eint2, c1AndNotCond)
                                .getResult();
    auto c2AndCondBool = rewriter
                             .create<mlir::toruslang::FHE::FromBoolOp>(
                                 op.getLoc(), eint2, c2AndCond)
                             .getResult();
    auto result = rewriter
                      .create<mlir::toruslang::FHE::AddEintOp>(
                          op.getLoc(), c1AndNotCondBool, c2AndCondBool)
                      .getResult();
    rewriter.replaceOpWithNewOp<mlir::toruslang::FHE::ToBoolOp>(op, boolType,
                                                                   result);
    return mlir::success();
  }
};

/// Performs the transformation of boolean operations
class FHEBooleanTransformPass
    : public FHEBooleanTransformBase<FHEBooleanTransformPass> {
public:
  void runOnOperation() override {
    mlir::Operation *op = getOperation();

    mlir::RewritePatternSet patterns(&getContext());
    patterns.add<GenGatePattern>(&getContext());
    patterns.add<MuxOpPattern>(&getContext());
    patterns.add<GeneralizeGatePattern<mlir::toruslang::FHE::BoolAndOp>>(
        &getContext(), llvm::SmallVector<uint64_t, 4>({0, 0, 0, 1}));
    patterns.add<GeneralizeGatePattern<mlir::toruslang::FHE::BoolNandOp>>(
        &getContext(), llvm::SmallVector<uint64_t, 4>({1, 1, 1, 0}));
    patterns.add<GeneralizeGatePattern<mlir::toruslang::FHE::BoolOrOp>>(
        &getContext(), llvm::SmallVector<uint64_t, 4>({0, 1, 1, 1}));
    patterns.add<GeneralizeGatePattern<mlir::toruslang::FHE::BoolXorOp>>(
        &getContext(), llvm::SmallVector<uint64_t, 4>({0, 1, 1, 0}));

    if (mlir::applyPatternsAndFoldGreedily(op, std::move(patterns)).failed()) {
      this->signalPassFailure();
    }
  }
};

} // end anonymous namespace

std::unique_ptr<mlir::OperationPass<>> createFHEBooleanTransformPass() {
  return std::make_unique<FHEBooleanTransformPass>();
}

} // namespace toruslang
} // namespace mlir
