# In your project CMakeLists.txt:
# 1. define the path containing torus-optimizer repository, built.
# TORUS_OPTIMIZER_DIR
# 2. add lines:
# add_subdirectory(${TORUS_OPTIMIZER_DIR}/torus-optimizer-cpp/cmake-utils)
# include_directories(${TORUS_OPTIMIZER_DIR}/torus-optimizer-cpp/src/cpp)

add_library(torus_optimizer STATIC ${TORUS_OPTIMIZER_DIR}/torus-optimizer-cpp/src/cpp/torus-optimizer.cpp)

target_link_libraries(torus_optimizer PRIVATE
  pthread m dl
  "${TORUS_OPTIMIZER_DIR}/target/libtorus_optimizer_cpp.a"
)

install(TARGETS torus_optimizer EXPORT torus_optimizer)
install(EXPORT torus_optimizer DESTINATION "./")
