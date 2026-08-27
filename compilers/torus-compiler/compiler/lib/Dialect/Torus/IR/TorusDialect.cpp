// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "toruslang/Dialect/Torus/IR/TorusDialect.h"
#include "toruslang/Dialect/Torus/IR/TorusOps.h"
#include "toruslang/Dialect/Torus/IR/TorusOpsDialect.cpp.inc"
#include "toruslang/Dialect/Torus/IR/TorusTypes.h"

#define GET_TYPEDEF_CLASSES
#include "toruslang/Dialect/Torus/IR/TorusOpsTypes.cpp.inc"

using namespace mlir::toruslang::Torus;

void TorusDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "toruslang/Dialect/Torus/IR/TorusOps.cpp.inc"
      >();

  addTypes<
#define GET_TYPEDEF_LIST
#include "toruslang/Dialect/Torus/IR/TorusOpsTypes.cpp.inc"
      >();
}
