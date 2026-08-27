// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe.com/torus-compiler-internal/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_OPTIMIZER_TRANSFORMS_PASSES_H
#define TORUSLANG_DIALECT_OPTIMIZER_TRANSFORMS_PASSES_H

#include <mlir/Dialect/Func/IR/FuncOps.h>
#include <mlir/Pass/Pass.h>

#include <toruslang/Dialect/FHE/IR/FHEDialect.h>
#include <toruslang/Dialect/Optimizer/IR/OptimizerDialect.h>
#include <toruslang/Dialect/Optimizer/IR/OptimizerOps.h>
#include <toruslang/Support/V0Parameters.h>

#define GEN_PASS_CLASSES
#include <toruslang/Dialect/FHE/Transforms/Optimizer/Optimizer.h.inc>

namespace mlir {
namespace toruslang {

std::unique_ptr<mlir::OperationPass<mlir::func::FuncOp>>
createOptimizerPartitionFrontierMaterializationPass(
    const optimizer::CircuitSolution &solverSolution);

} // namespace toruslang
} // namespace mlir

#endif
