// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe.com/torus-compiler-internal/blob/main/LICENSE.txt
// for license information.

#include "toruslang/Dialect/Optimizer/IR/OptimizerDialect.h"
#include "toruslang/Dialect/Optimizer/IR/OptimizerOps.h"

#include "toruslang/Dialect/Optimizer/IR/OptimizerOpsDialect.cpp.inc"

using namespace mlir::toruslang::Optimizer;

void OptimizerDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "toruslang/Dialect/Optimizer/IR/OptimizerOps.cpp.inc"
      >();
}
