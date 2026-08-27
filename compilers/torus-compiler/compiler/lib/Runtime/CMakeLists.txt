add_compile_options(-fsized-deallocation)

if(TORUSLANG_CUDA_SUPPORT)
  add_library(
    ToruslangRuntime SHARED
    context.cpp
    DFRuntime.cpp
    key_manager.cpp
    GPUDFG.cpp
    simulation.cpp
    wrappers.cpp
    time_util.cpp)
else()
  add_library(
    ToruslangRuntime SHARED
    context.cpp
    DFRuntime.cpp
    key_manager.cpp
    GPUDFG.cpp
    simulation.cpp
    wrappers.cpp
    time_util.cpp)
endif()

add_dependencies(ToruslangRuntime rust_deps_bundle torus-protocol)

if(TORUSLANG_DATAFLOW_EXECUTION_ENABLED)
  target_link_libraries(ToruslangRuntime PUBLIC HPX::hpx HPX::iostreams_component HPX::component)
  target_link_libraries(ToruslangRuntime PRIVATE hwloc)
  set_source_files_properties(DFRuntime.cpp PROPERTIES COMPILE_FLAGS "-fopenmp")
  add_dependencies(ToruslangRuntime HPXLibs)
endif()

if(TORUSLANG_CUDA_SUPPORT)
  target_link_libraries(ToruslangRuntime LINK_PUBLIC tfhe_cuda_backend)
  target_link_libraries(ToruslangRuntime PRIVATE hwloc)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  target_link_libraries(ToruslangRuntime PUBLIC omp)
else()
  target_link_libraries(ToruslangRuntime PUBLIC -Wl,--no-as-needed omp)
endif()

# Required to link with Torus
if(APPLE)
  find_library(SECURITY_FRAMEWORK Security)
  if(NOT SECURITY_FRAMEWORK)
    message(FATAL_ERROR "Security framework not found")
  endif()
  target_link_libraries(ToruslangRuntime LINK_PUBLIC ${SECURITY_FRAMEWORK})
endif()

target_include_directories(
  ToruslangRuntime
  PUBLIC ${TORUS_CPU_INCLUDE_DIR}
  PUBLIC ${TORUS_CPU_NOISE_MODEL_INCLUDE_DIR})

target_link_libraries(
  ToruslangRuntime
  PRIVATE pthread
          m
          dl
          $<TARGET_OBJECTS:mlir_c_runner_utils>
          $<TARGET_OBJECTS:mlir_float16_utils>
          $<TARGET_OBJECTS:MLIRSparseTensorRuntime>
          $<LINK_LIBRARY:WHOLE_ARCHIVE,ToruslangCommon>)

if(TORUSLANG_CUDA_SUPPORT)
  install(TARGETS ToruslangRuntime omp tfhe_cuda_backend EXPORT ToruslangRuntime)
else()
  install(TARGETS ToruslangRuntime omp EXPORT ToruslangRuntime)
endif()
install(EXPORT ToruslangRuntime DESTINATION "./")

#

add_library(
  ToruslangRuntimeStatic STATIC
  context.cpp
  DFRuntime.cpp
  key_manager.cpp
  GPUDFG.cpp
  simulation.cpp
  wrappers.cpp
  time_util.cpp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  target_link_libraries(ToruslangRuntimeStatic PUBLIC omp)
else()
  target_link_libraries(ToruslangRuntimeStatic PUBLIC -Wl,--no-as-needed omp)
endif()

target_include_directories(
  ToruslangRuntimeStatic
  PUBLIC ${TORUS_CPU_INCLUDE_DIR}
  PUBLIC ${TORUS_CPU_NOISE_MODEL_INCLUDE_DIR})

target_link_libraries(
  ToruslangRuntimeStatic
  PUBLIC rust_deps_bundle
         torus-protocol
         pthread
         m
         dl
         $<TARGET_OBJECTS:mlir_c_runner_utils>
         $<TARGET_OBJECTS:mlir_float16_utils>
         $<TARGET_OBJECTS:MLIRSparseTensorRuntime>)

if(TORUSLANG_DATAFLOW_EXECUTION_ENABLED)
  target_link_libraries(ToruslangRuntimeStatic PUBLIC HPX::hpx HPX::iostreams_component HPX::component)
endif()
