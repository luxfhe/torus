// Part of the Concrete Compiler Project, under the BSD3 License with Zama
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "toruslang/Dialect/TypeInference/IR/TypeInferenceDialect.h"
#include "toruslang/Dialect/TypeInference/IR/TypeInferenceOps.h"

#include "toruslang/Dialect/TypeInference/IR/TypeInferenceOpsDialect.cpp.inc"

using namespace mlir::toruslang::TypeInference;

void TypeInferenceDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "toruslang/Dialect/TypeInference/IR/TypeInferenceOps.cpp.inc"
      >();
}
