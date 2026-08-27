add_custom_target(EncodingsUnitTests)

add_dependencies(ToruslangUnitTests EncodingsUnitTests)

function(add_toruscompiler_lib_test test_name)
  add_unittest(EncodingsUnitTests ${test_name} ${ARGN})
  target_link_libraries(${test_name} PRIVATE ToruslangSupport ToruslangCommon ToruslangClientLib
                                             ToruslangServerLib ToruslangRuntime)
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

add_toruscompiler_lib_test(unit_tests_toruslang_Encodings Encodings_unit_tests.cpp)
