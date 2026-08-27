add_compile_options(-fexceptions -fsized-deallocation)

add_mlir_library(
  ToruslangSupport
  Pipeline.cpp
  CompilationFeedback.cpp
  CompilerEngine.cpp
  TFHECircuitKeys.cpp
  Encodings.cpp
  V0Parameters.cpp
  ProgramInfoGeneration.cpp
  logging.cpp
  LLVMEmitFile.cpp
  Utils.cpp
  DEPENDS
  mlir-headers
  torus-protocol
  LINK_LIBS
  PUBLIC
  FHELinalgDialect
  FHELinalgDialectTransforms
  FHETensorOpsToLinalg
  FHEDialectTransforms
  FHEToTFHECrt
  FHEToTFHEScalar
  SimulateTFHE
  ExtractSDFGOps
  MLIRLowerableDialectsToLLVM
  FHEDialectAnalysis
  FHEDialectTransforms
  RTDialectAnalysis
  ToruslangTransforms
  ToruslangTorusTransforms
  ToruslangSDFGTransforms
  ToruslangSDFGInterfaces
  LinalgExtras
  TFHEDialectTransforms
  rust_deps_bundle
  MLIRExecutionEngine
  ${LLVM_PTHREAD_LIB}
  TFHEDialectAnalysis
  TorusDialectAnalysis
  ToruslangRuntime)

target_include_directories(ToruslangSupport PUBLIC ${TORUS_CPU_INCLUDE_DIR})
