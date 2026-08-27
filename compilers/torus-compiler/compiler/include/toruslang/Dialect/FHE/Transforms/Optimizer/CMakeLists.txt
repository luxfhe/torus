set(LLVM_TARGET_DEFINITIONS Optimizer.td)
mlir_tablegen(Optimizer.h.inc -gen-pass-decls -name Transforms)
add_public_tablegen_target(ToruslangFHEOptimizerPassIncGen)
add_dependencies(mlir-headers ToruslangFHEOptimizerPassIncGen)
