add_mlir_dialect_library(
  ExtractSDFGOps
  ExtractSDFGOps.cpp
  ADDITIONAL_HEADER_DIRS
  ${PROJECT_SOURCE_DIR}/include/toruslang/Dialect/FHE
  DEPENDS
  SDFGDialect
  ToruslangSDFGInterfaces
  mlir-headers
  LINK_LIBS
  SDFGDialect
  ToruslangSDFGInterfaces
  PUBLIC
  MLIRIR
  MLIRSCFUtils
  MLIRTransforms)

target_link_libraries(ExtractSDFGOps PUBLIC MLIRIR)
