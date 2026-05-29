#ifndef TORUSLANG_FHE_BOOLEAN_PASS
#define TORUSLANG_FHE_BOOLEAN_PASS

include "mlir/Pass/PassBase.td"

def FHEBooleanTransform : Pass<"fhe-boolean-transform"> {
  let summary = "Transform FHE boolean operations to integer operations";
  let constructor = "mlir::toruslang::createFHEBooleanTransformPass()";
  let options = [];
  let dependentDialects = [ "mlir::toruslang::FHE::FHEDialect" ];
}

#endif
