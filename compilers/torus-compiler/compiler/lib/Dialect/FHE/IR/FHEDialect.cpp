// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "toruslang/Dialect/FHE/IR/FHEDialect.h"
#include "toruslang/Dialect/FHE/IR/FHEOps.h"
#include "toruslang/Dialect/FHE/IR/FHETypes.h"
#include "toruslang/Dialect/FHE/Interfaces/FHEInterfaces.h"

#define GET_ATTRDEF_CLASSES
#include "toruslang/Dialect/FHE/IR/FHEAttrs.cpp.inc"

#define GET_TYPEDEF_CLASSES
#include "toruslang/Dialect/FHE/IR/FHEOpsTypes.cpp.inc"

#include "toruslang/Dialect/FHE/IR/FHEOpsDialect.cpp.inc"

#include "toruslang/Support/Constants.h"

using namespace mlir::toruslang::FHE;

void FHEDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "toruslang/Dialect/FHE/IR/FHEOps.cpp.inc"
      >();

  addTypes<
#define GET_TYPEDEF_LIST
#include "toruslang/Dialect/FHE/IR/FHEOpsTypes.cpp.inc"
      >();

  addAttributes<
#define GET_ATTRDEF_LIST
#include "toruslang/Dialect/FHE/IR/FHEAttrs.cpp.inc"
      >();
}

mlir::LogicalResult EncryptedUnsignedIntegerType::verify(
    llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, unsigned p) {
  if (p == 0) {
    emitError() << "FHE.eint doesn't support precision of 0";
    return mlir::failure();
  }
  return mlir::success();
}

void EncryptedUnsignedIntegerType::print(mlir::AsmPrinter &p) const {
  p << "<" << getWidth() << ">";
}

mlir::Type EncryptedUnsignedIntegerType::parse(mlir::AsmParser &p) {
  if (p.parseLess())
    return mlir::Type();

  int width;

  if (p.parseInteger(width))
    return mlir::Type();

  if (p.parseGreater())
    return mlir::Type();

  mlir::Location loc = p.getEncodedSourceLoc(p.getNameLoc());

  return getChecked(loc, loc.getContext(), width);
}

mlir::LogicalResult EncryptedSignedIntegerType::verify(
    llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, unsigned p) {
  if (p == 0) {
    emitError() << "FHE.esint doesn't support precision of 0";
    return mlir::failure();
  }
  return mlir::success();
}

void EncryptedSignedIntegerType::print(mlir::AsmPrinter &p) const {
  p << "<" << getWidth() << ">";
}

mlir::Type EncryptedSignedIntegerType::parse(mlir::AsmParser &p) {
  if (p.parseLess())
    return mlir::Type();

  int width;

  if (p.parseInteger(width))
    return mlir::Type();

  if (p.parseGreater())
    return mlir::Type();

  mlir::Location loc = p.getEncodedSourceLoc(p.getNameLoc());

  return getChecked(loc, loc.getContext(), width);
}
