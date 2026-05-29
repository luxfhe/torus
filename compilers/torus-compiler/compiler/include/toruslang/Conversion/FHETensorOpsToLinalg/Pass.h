// Part of the Concrete Compiler Project, under the BSD3 License with Zama
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_CONVERSION_FHETENSOROPSTOLINALG_PASS_H_
#define TORUSLANG_CONVERSION_FHETENSOROPSTOLINALG_PASS_H_

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/Pass.h"

namespace mlir {
namespace toruslang {
/// Create a pass to convert `FHE` tensor operators to linal.generic
/// operators.
std::unique_ptr<mlir::OperationPass<mlir::func::FuncOp>>
createConvertFHETensorOpsToLinalg();
} // namespace toruslang
} // namespace mlir

#endif
