set(LLVM_TARGET_DEFINITIONS BigInt.td)
mlir_tablegen(BigInt.h.inc -gen-pass-decls -name Transforms)
add_public_tablegen_target(ToruslangFHEBigIntPassIncGen)
add_dependencies(mlir-headers ToruslangFHEBigIntPassIncGen)
