// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef LUXLANG_CONVERSION_LINALGEXTRAS_PASS_H_
#define LUXLANG_CONVERSION_LINALGEXTRAS_PASS_H_

#include "mlir/Pass/Pass.h"

namespace mlir {
namespace toruslang {
std::unique_ptr<OperationPass<ModuleOp>>
createLinalgGenericOpWithTensorsToLoopsPass(bool parallelizeLoops);
} // namespace toruslang
} // namespace mlir

#endif
