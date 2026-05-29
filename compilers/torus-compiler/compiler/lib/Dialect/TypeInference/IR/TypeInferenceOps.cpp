// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "toruslang/Dialect/TypeInference/IR/TypeInferenceOps.h"

namespace mlir {
namespace toruslang {
namespace TypeInference {} // namespace TypeInference
} // namespace toruslang
} // namespace mlir

#define GET_OP_CLASSES
#include "toruslang/Dialect/TypeInference/IR/TypeInferenceOps.cpp.inc"
