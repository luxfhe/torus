add_custom_target(ToruslangClientlibTests)

add_dependencies(ToruslangUnitTests ToruslangClientlibTests)

add_unittest(ToruslangClientlibTests unit_tests_toruslang_clientlib CRT.cpp)

target_link_libraries(unit_tests_toruslang_clientlib PRIVATE ToruslangCommon ToruslangClientLib
                                                                ToruslangSupport)
