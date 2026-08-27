#ifndef TORUSLANG_FHELINALG_TILING_PASS
#define TORUSLANG_FHELINALG_TILING_PASS

include "mlir/Pass/PassBase.td"

def CollapseParallelLoops : Pass<"collapse-parallel-loops", "mlir::ModuleOp"> {
  let summary =
      "Coalesce nested scf.for operations that are marked with "
      "the custom attribute parallel = true into a single scf.for "
      "loop which can subsequently be converted to scf.parallel.";
  let constructor = "mlir::toruslang::createCollapseParallelLoops()";
  let dependentDialects = ["mlir::scf::SCFDialect"];
}

def ForLoopToParallel : Pass<"for-loop-to-parallel", "mlir::ModuleOp"> {
  let summary =
      "Transform scf.for marked with the custom attribute parallel = true loop "
      "to scf.parallel after the bufferization";
  let constructor = "mlir::toruslang::createForLoopToParallel()";
  let dependentDialects = ["mlir::scf::SCFDialect"];
}

def Batching : Pass<"torus", "mlir::ModuleOp"> {
  let summary =
      "Hoists operation for which a batched version exists out of loops applying "
      "the operation to values stored in a tensor.";
  let constructor = "mlir::toruslang::createBatchingPass()";
}

def SCFForallToSCFFor : Pass<"scf-forall-to-scf-for", "mlir::ModuleOp"> {
  let summary = "Replaces all occurrences of scf.forall with equivalent loop nests of scf.for";
  let description = [{ Replaces all occurrences of scf.forall with equivalent loop nests of scf.for }];
  let constructor = "mlir::toruslang::createSCFForallToSCFForPass()";
  let dependentDialects = ["mlir::scf::SCFDialect"];
}

def LinalgFillToLinalgGeneric : Pass<"linalg-fill-to-linalg-generic", "mlir::ModuleOp"> {
  let summary = "Replaces all occurrences of linalg.fill with tensor.generate";
  let description = [{ Replaces all occurrences of linalg.fill with tensor.generate }];
  let constructor = "mlir::toruslang::createLinalgFillToLinalgGenericPass()";
  let dependentDialects = ["mlir::linalg::LinalgDialect"];
}

#endif
