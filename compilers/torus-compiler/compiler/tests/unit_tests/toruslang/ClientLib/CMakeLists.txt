add_custom_target(ConcretelangClientlibTests)

add_dependencies(ConcretelangUnitTests ConcretelangClientlibTests)

add_unittest(ConcretelangClientlibTests unit_tests_toruslang_clientlib CRT.cpp)

target_link_libraries(unit_tests_toruslang_clientlib PRIVATE ConcretelangCommon ConcretelangClientLib
                                                                ConcretelangSupport)
