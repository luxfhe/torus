if(TORUSLANG_UNIT_TESTS OR TORUSLANG_BENCHMARK)
  add_subdirectory(end_to_end_fixture)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR})
endif()

if(TORUSLANG_UNIT_TESTS)
  add_subdirectory(unit_tests)
  add_subdirectory(end_to_end_tests)
endif()

if(TORUSLANG_BENCHMARK)
  add_subdirectory(end_to_end_benchmarks)
endif()
