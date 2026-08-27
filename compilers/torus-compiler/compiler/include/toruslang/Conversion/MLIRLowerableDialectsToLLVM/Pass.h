// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_CONVERSION_MLIRLOWERABLEDIALECTSTOLLVM_PASS_H_
#define TORUSLANG_CONVERSION_MLIRLOWERABLEDIALECTSTOLLVM_PASS_H_

#include "mlir/Pass/Pass.h"

namespace mlir {
template <typename T> class OperationPass;
namespace toruslang {
/// Create a pass to convert MLIR lowerable dialects to LLVM.
std::unique_ptr<OperationPass<ModuleOp>>
createConvertMLIRLowerableDialectsToLLVMPass();
} // namespace toruslang
} // namespace mlir

#endif
