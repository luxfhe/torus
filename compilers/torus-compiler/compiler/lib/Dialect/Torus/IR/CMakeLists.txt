add_mlir_dialect_library(
  TorusDialect
  TorusDialect.cpp
  TorusOps.cpp
  ADDITIONAL_HEADER_DIRS
  ${PROJECT_SOURCE_DIR}/include/toruslang/Dialect/Torus
  DEPENDS
  mlir-headers
  LINK_LIBS
  PUBLIC
  MLIRIR)

target_link_libraries(TorusDialect PUBLIC MLIRIR)
