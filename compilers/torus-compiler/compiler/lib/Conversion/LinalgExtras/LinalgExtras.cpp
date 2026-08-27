// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include <toruslang/Conversion/Passes.h>
#include <toruslang/Support/LinalgExtras.h>
#include <mlir/Dialect/Linalg/IR/Linalg.h>
#include <mlir/Transforms/GreedyPatternRewriteDriver.h>

namespace {
struct LinalgGenericOpWithTensorsToLoopsPass
    : public LinalgGenericOpWithTensorsToLoopsBase<
          LinalgGenericOpWithTensorsToLoopsPass> {
  LinalgGenericOpWithTensorsToLoopsPass() = delete;
  LinalgGenericOpWithTensorsToLoopsPass(bool parallelizeLoops)
      : parallelizeLoops(parallelizeLoops){};
  void runOnOperation() final;

private:
  bool parallelizeLoops;
};
} // namespace

template <typename LoopType>
class LinalgRewritePattern
    : public mlir::OpRewritePattern<mlir::linalg::GenericOp> {
public:
  using OpRewritePattern<mlir::linalg::GenericOp>::OpRewritePattern;

  LinalgRewritePattern(::mlir::MLIRContext *context, bool parallelizeLoops,
                       mlir::PatternBenefit benefit = 0)
      : ::mlir::OpRewritePattern<mlir::linalg::GenericOp>(context, benefit),
        parallelizeLoops(parallelizeLoops) {}

  mlir::LogicalResult
  matchAndRewrite(mlir::linalg::GenericOp linalgOp,
                  mlir::PatternRewriter &rewriter) const override {
    mlir::FailureOr<mlir::linalg::LinalgLoops> loops =
        mlir::toruslang::linalgextras::linalgTensorOpToLoopsImpl<LoopType>(
            rewriter, linalgOp, parallelizeLoops);

    if (((mlir::LogicalResult)loops).failed() || loops->size() == 0)
      return mlir::failure();

    rewriter.replaceOp(linalgOp, loops.value()[0]->getResult(0));

    return mlir::success();
  };

private:
  bool parallelizeLoops;
};

void LinalgGenericOpWithTensorsToLoopsPass::runOnOperation() {
  auto op = this->getOperation();

  mlir::RewritePatternSet patterns(&getContext());
  patterns.insert<LinalgRewritePattern<mlir::scf::ForOp>>(&getContext(),
                                                          parallelizeLoops);
  (void)applyPatternsAndFoldGreedily(op, std::move(patterns));
}

namespace mlir {
namespace toruslang {
std::unique_ptr<OperationPass<ModuleOp>>
createLinalgGenericOpWithTensorsToLoopsPass(bool parallelizeLoops) {
  return std::make_unique<LinalgGenericOpWithTensorsToLoopsPass>(
      parallelizeLoops);
}
} // namespace toruslang
} // namespace mlir
