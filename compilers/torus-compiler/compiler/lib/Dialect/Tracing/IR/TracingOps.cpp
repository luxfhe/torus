// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "mlir/IR/Region.h"

#include "toruslang/Dialect/Torus/IR/TorusTypes.h"
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
