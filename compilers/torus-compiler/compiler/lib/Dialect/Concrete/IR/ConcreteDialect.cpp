// Part of the Concrete Compiler Project, under the BSD3 License with Zama
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "toruslang/Dialect/Concrete/IR/ConcreteDialect.h"
#include "toruslang/Dialect/Concrete/IR/ConcreteOps.h"
#include "toruslang/Dialect/Concrete/IR/ConcreteOpsDialect.cpp.inc"
#include "toruslang/Dialect/Concrete/IR/ConcreteTypes.h"

#define GET_TYPEDEF_CLASSES
#include "toruslang/Dialect/Concrete/IR/ConcreteOpsTypes.cpp.inc"

using namespace mlir::toruslang::Concrete;

void ConcreteDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "toruslang/Dialect/Concrete/IR/ConcreteOps.cpp.inc"
      >();

  addTypes<
#define GET_TYPEDEF_LIST
#include "toruslang/Dialect/Concrete/IR/ConcreteOpsTypes.cpp.inc"
      >();
}
