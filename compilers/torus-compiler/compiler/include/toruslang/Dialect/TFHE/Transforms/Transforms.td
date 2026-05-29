#ifndef TORUSLANG_TFHE_TRANSFORMS_PASS
#define TORUSLANG_TFHE_TRANSFORMS_PASS

include "mlir/Pass/PassBase.td"

def TFHEOptimization : Pass<"tfhe-optimization"> {
  let summary = "Optimize TFHE operations";
  let constructor = "mlir::toruslang::createTFHEOptimizationPass()";
  let options = [];
  let dependentDialects = [ "mlir::toruslang::TFHE::TFHEDialect" ];
}

def TFHEOperationTransformations : Pass<"tfhe-operation-transformations", "mlir::func::FuncOp"> {
  let summary = "Transform operations on TFHE types to other operations on TFHE types";
  let constructor = "mlir::toruslang::createTFHEOperationTransformationsPass()";
  let options = [];
  let dependentDialects = [ "mlir::toruslang::TFHE::TFHEDialect" ];
}

def TFHECircuitSolutionParametrization : Pass<"tfhe-circuit-solution-parametrization", "mlir::ModuleOp"> {
  let summary = "Parametrize TFHE with a circuit solution given by the optimizer";
  let constructor = "mlir::toruslang::createTFHECircuitSolutionParametrizationPass()";
  let options = [];
  let dependentDialects = [ "mlir::toruslang::TFHE::TFHEDialect" ];
}

#endif
