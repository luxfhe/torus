// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_FHE_ANALYSIS_UTILS_H
#define TORUSLANG_DIALECT_FHE_ANALYSIS_UTILS_H

#include <mlir/Dialect/Linalg/IR/Linalg.h>
#include <mlir/IR/BuiltinOps.h>

namespace mlir {
namespace toruslang {
namespace fhe {
namespace utils {

bool isEncryptedValue(mlir::Value value);
unsigned int getEintPrecision(mlir::Value value);

/// \brief Returns the loop range on a linalg.genric operation.
///
/// \param op
/// \return llvm::SmallVector<int64_t>
llvm::SmallVector<int64_t>
getLinalgGenericLoopRange(mlir::linalg::GenericOp op);

} // namespace utils
} // namespace fhe
} // namespace toruslang
} // namespace mlir

#endif
