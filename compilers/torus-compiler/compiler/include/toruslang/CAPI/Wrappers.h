// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_CAPI_WRAPPERS_H
#define TORUSLANG_CAPI_WRAPPERS_H

#include "toruslang-c/Support/CompilerEngine.h"
#include "toruslang/Support/CompilerEngine.h"
#include "toruslang/Support/LibrarySupport.h"

/// Add a mechanism to go from Cpp objects to C-struct, with the ability to
/// represent errors. Also the other way around.
#define DEFINE_C_API_PTR_METHODS_WITH_ERROR(name, cpptype)                     \
  static inline name wrap(cpptype *cpp) { return name{cpp, (char *)NULL}; }    \
  static inline name wrap(cpptype *cpp, std::string errorStr) {                \
    char *error = new char[errorStr.size()];                                   \
    strcpy(error, errorStr.c_str());                                           \
    return name{(cpptype *)NULL, error};                                       \
  }                                                                            \
  static inline cpptype *unwrap(name c) {                                      \
    return static_cast<cpptype *>(c.ptr);                                      \
  }                                                                            \
  static inline const char *getErrorPtr(name c) { return c.error; }

DEFINE_C_API_PTR_METHODS_WITH_ERROR(CompilerEngine,
                                    mlir::toruslang::CompilerEngine)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(CompilationContext,
                                    mlir::toruslang::CompilationContext)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(
    CompilationResult, mlir::toruslang::CompilerEngine::CompilationResult)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(Library,
                                    mlir::toruslang::CompilerEngine::Library)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(
    LibraryCompilationResult, mlir::toruslang::LibraryCompilationResult)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(LibrarySupport,
                                    mlir::toruslang::LibrarySupport)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(CompilationOptions,
                                    mlir::toruslang::CompilationOptions)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(OptimizerConfig,
                                    mlir::toruslang::optimizer::Config)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(ServerLambda,
                                    mlir::toruslang::serverlib::ServerLambda)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(
    ClientParameters, mlir::toruslang::clientlib::ClientParameters)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(KeySet,
                                    mlir::toruslang::clientlib::KeySet)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(KeySetCache,
                                    mlir::toruslang::clientlib::KeySetCache)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(
    EvaluationKeys, mlir::toruslang::clientlib::EvaluationKeys)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(LambdaArgument,
                                    mlir::toruslang::LambdaArgument)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(
    PublicArguments, mlir::toruslang::clientlib::PublicArguments)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(PublicResult,
                                    mlir::toruslang::clientlib::PublicResult)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(CompilationFeedback,
                                    mlir::toruslang::CompilationFeedback)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(Encoding,
                                    mlir::toruslang::clientlib::Encoding)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(
    EncryptionGate, mlir::toruslang::clientlib::EncryptionGate)
DEFINE_C_API_PTR_METHODS_WITH_ERROR(CircuitGate,
                                    mlir::toruslang::clientlib::CircuitGate)

#undef DEFINE_C_API_PTR_METHODS_WITH_ERROR

#endif
