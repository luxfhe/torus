// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_CONVERSION_EXTRACTSDFGOPS_PASS_H_
#define TORUSLANG_CONVERSION_EXTRACTSDFGOPS_PASS_H_

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/Pass.h"

namespace mlir {
namespace toruslang {
std::unique_ptr<OperationPass<mlir::func::FuncOp>>
createExtractSDFGOpsPass(bool unroll);
} // namespace toruslang
} // namespace mlir

#endif
