// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef LUXLANG_CONVERSION_CONCRETETOCAPI_PASS_H_
#define LUXLANG_CONVERSION_CONCRETETOCAPI_PASS_H_

#include "mlir/Pass/Pass.h"

namespace mlir {
namespace toruslang {
/// Create a pass to convert `Concrete` dialect to CAPI calls.
std::unique_ptr<OperationPass<ModuleOp>>
createConvertConcreteToCAPIPass(bool gpu);
} // namespace toruslang
} // namespace mlir

#endif
