add_mlir_dialect_library(
  TorusToCAPI
  TorusToCAPI.cpp
  ADDITIONAL_HEADER_DIRS
  ${PROJECT_SOURCE_DIR}/include/toruslang/Dialect/Torus
  DEPENDS
  TorusDialect
  mlir-headers
  LINK_LIBS
  PUBLIC
  MLIRIR
  MLIRTransforms)

target_link_libraries(TorusToCAPI PUBLIC TorusDialect MLIRIR)
