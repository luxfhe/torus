#ifndef TORUSLANG_DIALECT_FHE_ANALYSIS_TORUS_OPTIMIZER
#define TORUSLANG_DIALECT_FHE_ANALYSIS_TORUS_OPTIMIZER

include "mlir/Pass/PassBase.td"

def TorusOptimizer : Pass<"TorusOptimizer", "::mlir::func::FuncOp"> {
  let summary = "Call torus-optimizer";
  let description = [{
   The pass calls the torus-optimizer to provide crypto parameter.
   It construct a simplified representation of the FHE circuit and send it to the torus optimizer.
   It uses on the values from the MANP pass to indicate how noise is propagate and amplified in levelled operations.
  }];
}

#endif
