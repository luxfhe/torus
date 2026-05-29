#ifndef TORUSLANG_FHE_BIGINT_PASS
#define TORUSLANG_FHE_BIGINT_PASS

include "mlir/Pass/PassBase.td"

def FHEBigIntTransform : Pass<"fhe-big-int-transform"> {
  let summary = "Transform FHE operations on big integer into operations on chunks of small integer";
  let constructor = "mlir::toruslang::createFHEBigIntTransformPass()";
  let options = [];
  let dependentDialects = [ "mlir::toruslang::FHE::FHEDialect" ];
}

#endif
