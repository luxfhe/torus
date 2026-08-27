set(LLVM_TARGET_DEFINITIONS Boolean.td)
mlir_tablegen(Boolean.h.inc -gen-pass-decls -name Transforms)
add_public_tablegen_target(ToruslangFHEBooleanPassIncGen)
add_dependencies(mlir-headers ToruslangFHEBooleanPassIncGen)
