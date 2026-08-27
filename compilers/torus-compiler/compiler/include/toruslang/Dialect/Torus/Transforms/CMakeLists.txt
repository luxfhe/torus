set(LLVM_TARGET_DEFINITIONS Passes.td)
mlir_tablegen(Passes.h.inc -gen-pass-decls -name Torus)
add_public_tablegen_target(TorusTransformsIncGen)
