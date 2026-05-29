// Part of the Concrete Compiler Project, under the BSD3 License with Zama
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_RT_ANALYSIS_AUTOPAR_H
#define TORUSLANG_DIALECT_RT_ANALYSIS_AUTOPAR_H

#include <toruslang/Dialect/RT/IR/RTOps.h>
#include <functional>
#include <mlir/Pass/Pass.h>

namespace mlir {

class LLVMTypeConverter;
class BufferizeTypeConverter;
class RewritePatternSet;

namespace toruslang {
std::unique_ptr<mlir::Pass> createBuildDataflowTaskGraphPass();
std::unique_ptr<mlir::Pass> createLowerDataflowTasksPass();
std::unique_ptr<mlir::Pass> createBufferizeDataflowTaskOpsPass();
std::unique_ptr<mlir::Pass> createFinalizeTaskCreationPass();
std::unique_ptr<mlir::Pass> createStartStopPass(bool useOMP);
std::unique_ptr<mlir::Pass> createFixupBufferDeallocationPass();
void populateRTToLLVMConversionPatterns(mlir::LLVMTypeConverter &converter,
                                        mlir::RewritePatternSet &patterns);
void populateRTBufferizePatterns(mlir::BufferizeTypeConverter &typeConverter,
                                 mlir::RewritePatternSet &patterns);
} // namespace toruslang
} // namespace mlir

#endif
