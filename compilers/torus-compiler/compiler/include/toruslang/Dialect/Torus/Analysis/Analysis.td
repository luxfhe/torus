#ifndef TORUSLANG_DIALECT_TORUS_ANALYSIS
#define TORUSLANG_DIALECT_TORUS_ANALYSIS

include "mlir/Pass/PassBase.td"

def MemoryUsage : Pass<"MemoryUsage", "::mlir::ModuleOp"> {
  let summary = "Compute memory usage";
  let description = [{
    Computes memory usage per location, and provides those numbers throught the CompilationFeedback.
  }];
}

#endif
