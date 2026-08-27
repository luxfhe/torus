add_compile_options(-fexceptions)

add_mlir_library(
  ToruslangClientLib
  ClientLib.cpp
  ADDITIONAL_HEADER_DIRS
  ${PROJECT_SOURCE_DIR}/include/toruslang/ClientLib
  ${PROJECT_SOURCE_DIR}/include/toruslang/Common
  ${TORUS_CPU_INCLUDE_DIR}
  LINK_LIBS
  ToruslangCommon
  PUBLIC
  rust_deps_bundle
  torus-protocol)
