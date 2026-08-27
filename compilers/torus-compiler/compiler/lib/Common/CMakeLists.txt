add_compile_options(-fexceptions -fsized-deallocation -fno-rtti)

add_mlir_library(
  ToruslangCommon
  Protocol.cpp
  CRT.cpp
  Csprng.cpp
  Keys.cpp
  Keysets.cpp
  Transformers.cpp
  Security.cpp
  Values.cpp
  LINK_LIBS
  PUBLIC
  rust_deps_bundle
  torus-protocol
  capnp
  kj)

target_include_directories(
  ToruslangCommon
  PUBLIC ${TORUS_CPU_INCLUDE_DIR}
  PUBLIC ${TORUS_CPU_NOISE_MODEL_INCLUDE_DIR})
