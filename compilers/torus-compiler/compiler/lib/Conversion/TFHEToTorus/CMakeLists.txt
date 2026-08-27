add_mlir_dialect_library(
  TFHEToTorus
  TFHEToTorus.cpp
  ADDITIONAL_HEADER_DIRS
  ${PROJECT_SOURCE_DIR}/include/toruslang/Dialect/TFHE
  DEPENDS
  TFHEDialect
  TorusDialect
  mlir-headers
  LINK_LIBS
  PUBLIC
  MLIRIR
  MLIRTransforms
  MLIRMathDialect)

target_link_libraries(TFHEToTorus PUBLIC MLIRIR)
