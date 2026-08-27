// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_TORUS_MEMORY_USAGE_H
#define TORUSLANG_DIALECT_TORUS_MEMORY_USAGE_H

#include <mlir/IR/BuiltinOps.h>
#include <mlir/Pass/Pass.h>

#include <toruslang/Support/CompilationFeedback.h>

namespace mlir {
namespace toruslang {

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>>
createMemoryUsagePass(ProgramCompilationFeedback &feedback);

} // namespace toruslang
} // namespace mlir

#endif
