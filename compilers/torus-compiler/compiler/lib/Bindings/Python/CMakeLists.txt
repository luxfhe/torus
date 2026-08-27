include(AddMLIRPython)

# Python bindings need to throw exceptions for proper handling of errors on the python-side
add_compile_options(-fexceptions)

# ######################################################################################################################
# Declare native Python extension
# ######################################################################################################################

declare_mlir_python_sources(ToruslangBindingsPythonExtension)

declare_mlir_python_extension(
  ToruslangBindingsPythonExtension.Core
  MODULE_NAME
  _toruslang
  ADD_TO_PARENT
  ToruslangBindingsPythonExtension
  SOURCES
  ToruslangModule.cpp
  FHEModule.cpp
  CompilerAPIModule.cpp
  EMBED_CAPI_LINK_LIBS
  MLIRCAPIRegisterEverything)

# ######################################################################################################################
# Declare python sources
# ######################################################################################################################

declare_mlir_python_sources(
  ToruslangBindingsPythonSources
  ROOT_DIR
  "${CMAKE_CURRENT_SOURCE_DIR}"
  SOURCES
  torus/compiler/__init__.py
  torus/compiler/compilation_feedback.py
  torus/compiler/compilation_context.py
  torus/compiler/tfhers_int.py
  torus/compiler/utils.py
  torus/__init__.py
  torus/lang/__init__.py
  torus/lang/dialects/__init__.py
  torus/lang/dialects/_ods_common.py)

# ######################################################################################################################
# Declare dialect-specific bindings.
# ######################################################################################################################

declare_mlir_python_sources(ToruslangBindingsPythonSources.Dialects ADD_TO_PARENT ToruslangBindingsPythonSources)

declare_mlir_dialect_python_bindings(
  ADD_TO_PARENT
  ToruslangBindingsPythonSources.Dialects
  ROOT_DIR
  "${CMAKE_CURRENT_SOURCE_DIR}"
  TORUSLANGBindingsPythonFHEOps
  TD_FILE
  torus/lang/dialects/FHEOps.td
  SOURCES
  torus/lang/dialects/fhe.py
  DIALECT_NAME
  FHE)

declare_mlir_dialect_python_bindings(
  ADD_TO_PARENT
  ToruslangBindingsPythonSources.Dialects
  ROOT_DIR
  "${CMAKE_CURRENT_SOURCE_DIR}"
  TORUSLANGBindingsPythonFHELinalgOps
  TD_FILE
  torus/lang/dialects/FHELinalgOps.td
  SOURCES
  torus/lang/dialects/fhelinalg.py
  DIALECT_NAME
  FHELinalg)

declare_mlir_dialect_python_bindings(
  ADD_TO_PARENT
  ToruslangBindingsPythonSources.Dialects
  ROOT_DIR
  "${CMAKE_CURRENT_SOURCE_DIR}"
  TORUSLANGBindingsPythonTracingOps
  TD_FILE
  torus/lang/dialects/TracingOps.td
  SOURCES
  torus/lang/dialects/tracing.py
  DIALECT_NAME
  Tracing)

# ######################################################################################################################
# Build composite binaries
# ######################################################################################################################

# Bundle our own, self-contained CAPI library with all of our deps.
add_mlir_python_common_capi_library(
  ToruslangBindingsPythonCAPI
  INSTALL_COMPONENT
  ToruslangBindingsPythonModules
  INSTALL_DESTINATION
  python_packages/toruslang_core/mlir/_mlir_libs
  # NOTE: When the MLIR API is relocated under toruslang, this would change to .../toruslang/_mlir_libs
  OUTPUT_DIRECTORY
  "${TORUSLANG_PYTHON_PACKAGES_DIR}/toruslang_core/mlir/_mlir_libs"
  RELATIVE_INSTALL_ROOT
  "../../../.."
  DECLARED_SOURCES
  # TODO: This can be chopped down significantly for size.
  MLIRPythonSources
  ToruslangBindingsPythonSources
  ToruslangBindingsPythonExtension)

target_include_directories(ToruslangBindingsPythonCAPI PUBLIC ${TORUS_CPU_INCLUDE_DIR})

target_link_libraries(
  ToruslangBindingsPythonCAPI
  PRIVATE $<LINK_LIBRARY:WHOLE_ARCHIVE,ToruslangSupport> $<LINK_LIBRARY:WHOLE_ARCHIVE,ToruslangClientLib>
          $<LINK_LIBRARY:WHOLE_ARCHIVE,ToruslangServerLib>)

# Bundle the MLIR python sources into our package. The MLIR API is position independent, so we explicitly output it to
# the mlir/ folder as a temporary measure. It will eventually migrate under the toruslang/ folder and be accessible
# under the unified "import toruslang..." namespace.
add_mlir_python_modules(
  ToruslangMLIRPythonModules
  ROOT_PREFIX
  "${TORUSLANG_PYTHON_PACKAGES_DIR}/toruslang_core/mlir"
  INSTALL_PREFIX
  "python_packages/toruslang_core/mlir"
  DECLARED_SOURCES
  MLIRPythonSources
  # We need the circt extensions co-located with the MLIR extensions. When the namespace is unified, this moves to the
  # below.
  ToruslangBindingsPythonExtension
  COMMON_CAPI_LINK_LIBS
  ToruslangBindingsPythonCAPI)

# Bundle the TORUSLANG python sources into our package.
add_mlir_python_modules(
  ToruslangPythonModules
  ROOT_PREFIX
  "${TORUSLANG_PYTHON_PACKAGES_DIR}/toruslang_core"
  INSTALL_PREFIX
  "python_packages/toruslang_core"
  DECLARED_SOURCES
  ToruslangBindingsPythonSources
  COMMON_CAPI_LINK_LIBS
  ToruslangBindingsPythonCAPI)
