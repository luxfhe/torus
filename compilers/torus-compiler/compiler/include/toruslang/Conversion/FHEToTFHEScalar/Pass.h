// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_CONVERSION_FHETOTFHESCALAR_PASS_H_
#define TORUSLANG_CONVERSION_FHETOTFHESCALAR_PASS_H_

#include "mlir/Pass/Pass.h"
#include "llvm/Support/Casting.h"
#include <list>

namespace mlir {
namespace toruslang {

struct ScalarLoweringParameters {
  size_t polynomialSize;
  ScalarLoweringParameters(size_t polySize) : polynomialSize(polySize){};
};

/// Create a pass to convert `FHE` dialect to `TFHE` dialect with the scalar
// strategy.
std::unique_ptr<OperationPass<mlir::ModuleOp>>
createConvertFHEToTFHEScalarPass(ScalarLoweringParameters loweringParameters);
} // namespace toruslang
} // namespace mlir

#endif
