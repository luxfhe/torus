// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_TORUS_TRANSFORMS_PASSES_H_
#define TORUSLANG_DIALECT_TORUS_TRANSFORMS_PASSES_H_

#include "mlir/Pass/Pass.h"

#define GEN_PASS_CLASSES
#include "toruslang/Dialect/Torus/Transforms/Passes.h.inc"

namespace mlir {
namespace toruslang {
std::unique_ptr<OperationPass<ModuleOp>> createAddRuntimeContext();
} // namespace toruslang
} // namespace mlir

#endif // TORUSLANG_DIALECT_TORUS_TRANSFORMS_PASSES_H_
