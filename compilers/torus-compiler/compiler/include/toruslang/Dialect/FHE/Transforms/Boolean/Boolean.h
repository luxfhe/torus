// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_FHE_BOOLEAN_PASS_H
#define TORUSLANG_FHE_BOOLEAN_PASS_H

#include <toruslang/Dialect/FHE/IR/FHEDialect.h>
#include <mlir/Pass/Pass.h>

#define GEN_PASS_CLASSES
#include <toruslang/Dialect/FHE/Transforms/Boolean/Boolean.h.inc>

namespace mlir {
namespace toruslang {

std::unique_ptr<mlir::OperationPass<>> createFHEBooleanTransformPass();

} // namespace toruslang
} // namespace mlir

#endif
