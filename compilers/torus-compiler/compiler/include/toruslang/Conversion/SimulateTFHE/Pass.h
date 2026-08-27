// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_CONVERSION_SIMULATE_TFHE_PASS_H_
#define TORUSLANG_CONVERSION_SIMULATE_TFHE_PASS_H_

#include "mlir/Pass/Pass.h"

namespace mlir {
namespace toruslang {
/// Create a pass that simulates TFHE operations
std::unique_ptr<OperationPass<ModuleOp>>
createSimulateTFHEPass(bool enableOverflowDetection);
} // namespace toruslang
} // namespace mlir

#endif
