// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_CONVERSION_TFHETOTORUS_PASS_H_
#define TORUSLANG_CONVERSION_TFHETOTORUS_PASS_H_

#include "mlir/Pass/Pass.h"

namespace mlir {
namespace toruslang {
/// Create a pass to convert `TFHE` dialect to `Torus` dialect.
std::unique_ptr<OperationPass<ModuleOp>> createConvertTFHEToTorusPass();
} // namespace toruslang
} // namespace mlir

#endif
