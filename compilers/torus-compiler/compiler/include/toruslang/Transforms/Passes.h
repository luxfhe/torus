// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_TRANSFORMS_PASS_H
#define TORUSLANG_TRANSFORMS_PASS_H

#include <mlir/Dialect/Func/IR/FuncOps.h>
#include <mlir/Dialect/Linalg/IR/Linalg.h>
#include <mlir/Dialect/MemRef/IR/MemRef.h>
#include <mlir/Dialect/SCF/IR/SCF.h>
#include <mlir/Pass/Pass.h>

#define GEN_PASS_CLASSES
#include <toruslang/Transforms/Passes.h.inc>

namespace mlir {
namespace toruslang {

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>>
createCollapseParallelLoops();
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createForLoopToParallel();
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>>
createBatchingPass(int64_t maxBatchSize = std::numeric_limits<int64_t>::max());
std::unique_ptr<OperationPass<ModuleOp>> createSCFForallToSCFForPass();
std::unique_ptr<OperationPass<ModuleOp>> createLinalgFillToLinalgGenericPass();
} // namespace toruslang
} // namespace mlir

#endif
