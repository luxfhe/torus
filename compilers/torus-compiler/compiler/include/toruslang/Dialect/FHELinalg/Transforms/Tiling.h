// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_LINALG_TILING_PASS_H
#define TORUSLANG_LINALG_TILING_PASS_H

#include <toruslang/Dialect/FHELinalg/IR/FHELinalgDialect.h>
#include <mlir/Dialect/Linalg/IR/Linalg.h>
#include <mlir/Pass/Pass.h>

#define GEN_PASS_CLASSES
#include <toruslang/Dialect/FHELinalg/Transforms/Tiling.h.inc>

namespace mlir {
namespace toruslang {
std::unique_ptr<mlir::OperationPass<>>
createFHELinalgTilingMarkerPass(llvm::ArrayRef<int64_t> tileSizes);

std::unique_ptr<mlir::OperationPass<>> createLinalgTilingPass();
} // namespace toruslang
} // namespace mlir

#endif
