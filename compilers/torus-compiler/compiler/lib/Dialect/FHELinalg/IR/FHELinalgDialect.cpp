// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "toruslang/Dialect/FHELinalg/IR/FHELinalgDialect.h"
#include "toruslang/Dialect/FHELinalg/IR/FHELinalgOps.h"
#include "toruslang/Dialect/FHELinalg/IR/FHELinalgTypes.h"

#define GET_TYPEDEF_CLASSES
#include "toruslang/Dialect/FHELinalg/IR/FHELinalgOpsTypes.cpp.inc"

#include "toruslang/Dialect/FHELinalg/IR/FHELinalgOpsDialect.cpp.inc"

using namespace mlir::toruslang::FHELinalg;

void FHELinalgDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "toruslang/Dialect/FHELinalg/IR/FHELinalgOps.cpp.inc"
      >();

  addTypes<
#define GET_TYPEDEF_LIST
#include "toruslang/Dialect/FHELinalg/IR/FHELinalgOpsTypes.cpp.inc"
      >();
}
