// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_FHE_BIGINT_PASS_H
#define TORUSLANG_FHE_BIGINT_PASS_H

#include <toruslang/Dialect/FHE/IR/FHEDialect.h>
#include <mlir/Pass/Pass.h>

#define GEN_PASS_CLASSES
#include <toruslang/Dialect/FHE/Transforms/BigInt/BigInt.h.inc>

namespace mlir {
namespace toruslang {

std::unique_ptr<mlir::OperationPass<>>
createFHEBigIntTransformPass(unsigned int chunkSize, unsigned int chunkWidth);

} // namespace toruslang
} // namespace mlir

#endif
