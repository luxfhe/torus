#ifndef TORUSLANG_FHE_MAX_PASS
#define TORUSLANG_FHE_MAX_PASS

include "mlir/Pass/PassBase.td"

def FHEMaxTransform : Pass<"fhe-max-transform"> {
  let summary = "Transform max operation to basic operations";
  let constructor = "mlir::toruslang::createFHEMaxTransformPass()";
  let options = [];
  let dependentDialects = [ "mlir::toruslang::FHE::FHEDialect" ];
}

#endif
