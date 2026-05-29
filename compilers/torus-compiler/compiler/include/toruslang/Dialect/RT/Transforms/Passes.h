// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe.com/torus-compiler-internal/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_RT_TRANSFORMS_PASSES_H
#define TORUSLANG_DIALECT_RT_TRANSFORMS_PASSES_H

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Pass/Pass.h"

#include "toruslang/Dialect/RT/IR/RTDialect.h"

#define GEN_PASS_CLASSES
#include "toruslang/Dialect/RT/Transforms/Passes.h.inc"

namespace mlir {
namespace toruslang {
std::unique_ptr<OperationPass<func::FuncOp>> createHoistAwaitFuturePass();
} // namespace toruslang
} // namespace mlir

#endif // TORUSLANG_DIALECT_RT_TRANSFORMS_PASSES_H
