// Part of the Concrete Compiler Project, under the BSD3 License with Zama
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_CONCRETE_TRANSFORMS_PASSES_H_
#define TORUSLANG_DIALECT_CONCRETE_TRANSFORMS_PASSES_H_

#include "mlir/Pass/Pass.h"

#define GEN_PASS_CLASSES
#include "toruslang/Dialect/Concrete/Transforms/Passes.h.inc"

namespace mlir {
namespace toruslang {
std::unique_ptr<OperationPass<ModuleOp>> createAddRuntimeContext();
} // namespace toruslang
} // namespace mlir

#endif // TORUSLANG_DIALECT_CONCRETE_TRANSFORMS_PASSES_H_
