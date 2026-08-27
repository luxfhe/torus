// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "mlir/IR/Builders.h"

#include "toruslang/Dialect/SDFG/IR/SDFGDialect.h"
#include "toruslang/Dialect/SDFG/IR/SDFGOps.h"
#include "toruslang/Dialect/SDFG/IR/SDFGTypes.h"

using namespace mlir::toruslang::SDFG;

#define GET_TYPEDEF_CLASSES
#include "toruslang/Dialect/SDFG/IR/SDFGTypes.cpp.inc"

void SDFGDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "toruslang/Dialect/SDFG/IR/SDFGOps.cpp.inc"
      >();

  addTypes<
#define GET_TYPEDEF_LIST
#include "toruslang/Dialect/SDFG/IR/SDFGTypes.cpp.inc"
      >();

  addAttributes<
#define GET_ATTRDEF_LIST
#include "toruslang/Dialect/SDFG/IR/SDFGAttributes.cpp.inc"
      >();
}

#define GET_ATTRDEF_CLASSES
#include "toruslang/Dialect/SDFG/IR/SDFGAttributes.cpp.inc"

#define GET_TYPEDEF_CLASSES
#include "toruslang/Dialect/SDFG/IR/SDFGDialect.cpp.inc"

void StreamType::print(mlir::AsmPrinter &p) const {
  p << "<" << getElementType() << ">";
}

mlir::Type StreamType::parse(mlir::AsmParser &p) {
  if (p.parseLess())
    return mlir::Type();

  mlir::Type t;
  if (p.parseType(t))
    return mlir::Type();

  if (p.parseGreater())
    return mlir::Type();

  mlir::Location loc = p.getEncodedSourceLoc(p.getNameLoc());

  return getChecked(loc, loc.getContext(), t);
}
