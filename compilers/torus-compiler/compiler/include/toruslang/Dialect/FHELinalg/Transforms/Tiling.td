#ifndef TORUSLANG_FHELINALG_TILING_PASS
#define TORUSLANG_FHELINALG_TILING_PASS

include "mlir/Pass/PassBase.td"

def FHELinalgTilingMarker : Pass<"fhe-linalg-tiling-marker"> {
  let summary =
      "Marks FHELinalg operations for tiling using a vector of tile sizes";
  let constructor = "mlir::toruslang::createFHELinalgTilingMarkerPass()";
  let options = [];
  let dependentDialects = [ "mlir::toruslang::FHELinalg::FHELinalgDialect" ];
}

def LinalgTiling : Pass<"fhe-linalg-tiling"> {
  let summary = "Performs tiling of Linalg operations based on the "
                "tile-size attribute";
  let constructor = "mlir::toruslang::createLinalgTilingPass()";
  let options = [];
  let dependentDialects = [ "mlir::linalg::LinalgDialect" ];
}

#endif
