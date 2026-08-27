// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_TFHE_OPTIMIZATION_PASS_H
#define TORUSLANG_TFHE_OPTIMIZATION_PASS_H

#include "torus-optimizer.hpp"
#include "toruslang/Dialect/TFHE/IR/TFHEDialect.h"
#include "mlir/Pass/Pass.h"

#define GEN_PASS_CLASSES
#include "toruslang/Dialect/TFHE/Transforms/Transforms.h.inc"

namespace mlir {
namespace toruslang {
std::unique_ptr<mlir::OperationPass<>> createTFHEOptimizationPass();
std::unique_ptr<mlir::OperationPass<mlir::func::FuncOp>>
createTFHEOperationTransformationsPass();
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>>
    createTFHECircuitSolutionParametrizationPass(
        std::optional<torus_optimizer::dag::CircuitSolution>);
} // namespace toruslang
} // namespace mlir

#endif
