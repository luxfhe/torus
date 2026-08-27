add_custom_target(SDFGUnitTests)

add_dependencies(ToruslangUnitTests SDFGUnitTests)

function(add_toruscompiler_lib_test test_name)
  add_unittest(SDFGUnitTests ${test_name} ${ARGN})
  target_link_libraries(${test_name} PRIVATE ToruslangSupport ToruslangClientLib ToruslangServerLib
                                             ToruslangRuntime)
  set_source_files_properties(${ARGN} PROPERTIES COMPILE_FLAGS "-fno-rtti")
endfunction()

if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  link_libraries(
    # useful for old gcc versions
    -Wl,--allow-multiple-definition # static torus-optimizer and torus shares some code
  )
endif()

if(TORUSLANG_DATAFLOW_EXECUTION_ENABLED)
  add_compile_options(-DTORUSLANG_DATAFLOW_TESTING_ENABLED)
endif()

add_toruscompiler_lib_test(unit_tests_toruslang_SDFG SDFG_unit_tests.cpp)
