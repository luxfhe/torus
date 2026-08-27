add_llvm_tool(toruscompiler main.cpp)
target_compile_options(toruscompiler PRIVATE -fexceptions)
llvm_update_compile_flags(toruscompiler)

get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)

add_dependencies(toruscompiler mlir-headers)

target_link_libraries(
  toruscompiler
  PRIVATE ${dialect_libs}
          ${conversion_libs}
          MLIRTransforms
          TorusDialect
          TFHEDialect
          FHEDialect
          SDFGDialect
          OptimizerDialect
          ToruslangTransforms
          MLIRIR
          MLIRLLVMIRTransforms
          MLIRLLVMToLLVMIRTranslation
          RTDialect
          ToruslangSupport
          ToruslangCommon)

mlir_check_all_link_libraries(toruscompiler)
