add_custom_target(TorusCompilerUnitTests)
add_compile_options(-fexceptions)

function(add_toruscompiler_unittest test_name)
  add_unittest(TorusCompilerUnitTests ${test_name} ${ARGN})
  target_link_libraries(${test_name} PRIVATE ToruslangSupport ToruslangClientLib ToruslangServerLib
                                             ToruslangRuntime EndToEndFixture ${RPATH_FLAGS})
  set_source_files_properties(${ARGN} PROPERTIES COMPILE_FLAGS "-fno-rtti")
endfunction()

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${TORUS_OPTIMIZER_DIR}/torus-optimizer-cpp/src/cpp)

if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  link_libraries(
    # useful for old gcc versions
    -Wl,--allow-multiple-definition # static torus-optimizer and torus shares some code
  )
endif()

if(TORUSLANG_DATAFLOW_EXECUTION_ENABLED)
  add_compile_options(-DTORUSLANG_DATAFLOW_TESTING_ENABLED)
endif()

add_toruscompiler_unittest(end_to_end_jit_chunked_int end_to_end_jit_chunked_int.cc globals.cc)

add_toruscompiler_unittest(end_to_end_jit_test end_to_end_jit_test.cc globals.cc)

add_toruscompiler_unittest(end_to_end_test end_to_end_test.cc globals.cc)

add_toruscompiler_unittest(end_to_end_jit_lambda end_to_end_jit_lambda.cc globals.cc)
