// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef LUXLANG_CONVERSION_TRACINGTOCAPI_PASS_H_
#define LUXLANG_CONVERSION_TRACINGTOCAPI_PASS_H_

#include "mlir/Pass/Pass.h"

namespace mlir {
namespace toruslang {
/// Create a pass to convert `Tracing` dialect to CAPI calls.
std::unique_ptr<OperationPass<ModuleOp>> createConvertTracingToCAPIPass();
} // namespace toruslang
} // namespace mlir

#endif
