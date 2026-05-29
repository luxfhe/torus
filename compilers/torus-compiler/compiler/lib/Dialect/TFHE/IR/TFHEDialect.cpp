// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "toruslang/Dialect/TFHE/IR/TFHEDialect.h"
#include "toruslang/Dialect/TFHE/IR/TFHEOps.h"
#include "toruslang/Dialect/TFHE/IR/TFHEParameters.h"

#define GET_ATTRDEF_CLASSES
#include "toruslang/Dialect/TFHE/IR/TFHEAttrs.cpp.inc"

#define GET_TYPEDEF_CLASSES
#include "toruslang/Dialect/TFHE/IR/TFHEOpsTypes.cpp.inc"

#include "toruslang/Dialect/TFHE/IR/TFHEOpsDialect.cpp.inc"

#include "toruslang/Support/Constants.h"
#include "toruslang/Support/Variants.h"

using namespace mlir::toruslang::TFHE;

void TFHEDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "toruslang/Dialect/TFHE/IR/TFHEOps.cpp.inc"
      >();

  addTypes<
#define GET_TYPEDEF_LIST
#include "toruslang/Dialect/TFHE/IR/TFHEOpsTypes.cpp.inc"
      >();

  addAttributes<
#define GET_ATTRDEF_LIST
#include "toruslang/Dialect/TFHE/IR/TFHEAttrs.cpp.inc"
      >();
}

/// Verify that GLWE parameter are consistent
::mlir::LogicalResult GLWECipherTextType::verify(
    ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError,
    GLWESecretKey key) {
  return std::visit(
      overloaded{[](GLWESecretKeyNone sk) { return mlir::success(); },
                 [&](GLWESecretKeyParameterized sk) {
                   if (sk.dimension == 0) {
                     emitError() << "GLWE key has zero dimension.";
                     return ::mlir::failure();
                   }
                   if (sk.polySize == 0) {
                     emitError() << "GLWE key has zero poly size.";
                     return ::mlir::failure();
                   }
                   return mlir::success();
                 },
                 [&](GLWESecretKeyNormalized sk) {
                   if (sk.dimension == 0) {
                     emitError() << "GLWE key has zero dimension.";
                     return ::mlir::failure();
                   }
                   if (sk.polySize == 0) {
                     emitError() << "GLWE key has zero poly size.";
                     return ::mlir::failure();
                   }
                   return mlir::success();
                 }},
      key.inner);
}
