// Part of the Concrete Compiler Project, under the BSD3 License with Zama
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_CONVERSION_TFHEGLOBALPARAMETRIZATION_PASS_H_
#define TORUSLANG_CONVERSION_TFHEGLOBALPARAMETRIZATION_PASS_H_

#include "mlir/Pass/Pass.h"

#include "toruslang/Conversion/Utils/GlobalFHEContext.h"

namespace mlir {
namespace toruslang {
/// Create a pass to inject fhe parameters to the TFHE types and operators.
std::unique_ptr<OperationPass<ModuleOp>>
createConvertTFHEGlobalParametrizationPass(const V0Parameter parameter);
} // namespace toruslang
} // namespace mlir

#endif
