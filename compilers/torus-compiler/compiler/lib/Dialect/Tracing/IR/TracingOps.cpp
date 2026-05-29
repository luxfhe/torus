// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "mlir/IR/Region.h"

#include "toruslang/Dialect/Concrete/IR/ConcreteTypes.h"
#include "toruslang/Dialect/FHE/IR/FHEOps.h"
#include "toruslang/Dialect/TFHE/IR/TFHETypes.h"
#include "toruslang/Dialect/Tracing/IR/TracingOps.h"

namespace mlir {
namespace toruslang {
namespace Tracing {} // namespace Tracing
} // namespace toruslang
} // namespace mlir

#define GET_OP_CLASSES
#include "toruslang/Dialect/Tracing/IR/TracingOps.cpp.inc"
