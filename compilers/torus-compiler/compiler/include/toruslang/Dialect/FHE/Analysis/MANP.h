// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_FHE_ANALYSIS_MANP_H
#define TORUSLANG_DIALECT_FHE_ANALYSIS_MANP_H

#include <functional>
#include <mlir/Pass/Pass.h>

namespace mlir {
namespace toruslang {
bool isEncryptedValue(mlir::Value value);
unsigned int getEintPrecision(mlir::Value value);
std::unique_ptr<mlir::Pass> createMANPPass(bool debug = false);

std::unique_ptr<mlir::Pass>
createMaxMANPPass(std::function<void(uint64_t, unsigned)> setMax);
} // namespace toruslang
} // namespace mlir

#endif
