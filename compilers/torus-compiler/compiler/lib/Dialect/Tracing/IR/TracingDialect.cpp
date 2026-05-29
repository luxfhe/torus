// Part of the Concrete Compiler Project, under the BSD3 License with Zama
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "toruslang/Dialect/Tracing/IR/TracingDialect.h"
#include "toruslang/Dialect/Tracing/IR/TracingOps.h"

#include "toruslang/Dialect/Tracing/IR/TracingOpsDialect.cpp.inc"

#include "toruslang/Support/Constants.h"

using namespace mlir::toruslang::Tracing;

void TracingDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "toruslang/Dialect/Tracing/IR/TracingOps.cpp.inc"
      >();
}
