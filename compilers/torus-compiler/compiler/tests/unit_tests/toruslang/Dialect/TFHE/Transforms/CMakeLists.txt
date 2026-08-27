add_custom_target(ToruslangTFHETransformsTests)

add_dependencies(ToruslangUnitTests ToruslangTFHETransformsTests)

add_unittest(ToruslangTFHETransformsTests unit_tests_toruslang_tfhe_transforms Parametrization.cpp)

target_link_libraries(
  unit_tests_toruslang_tfhe_transforms
  PRIVATE TFHEDialectTransforms
          MLIRParser
          MLIRExecutionEngine
          TFHEGlobalParametrization
          ToruslangSupport
          ToruslangClientLib
          ToruslangServerLib
          ToruslangCommon)
