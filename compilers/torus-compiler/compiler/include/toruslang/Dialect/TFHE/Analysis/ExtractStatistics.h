// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_TFHE_ANALYSIS_EXTRACT_STATISTICS_H
#define TORUSLANG_DIALECT_TFHE_ANALYSIS_EXTRACT_STATISTICS_H

#include <mlir/IR/BuiltinOps.h>
#include <mlir/Pass/Pass.h>

#include <toruslang/Support/CompilationFeedback.h>

namespace mlir {
namespace toruslang {

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>>
createStatisticExtractionPass(ProgramCompilationFeedback &feedback);
} // namespace toruslang
} // namespace mlir

#endif
