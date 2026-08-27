// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe.com/torus-compiler-internal/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_OPTIMIZER_IR_OPTIMIZEROPS_H
#define TORUSLANG_DIALECT_OPTIMIZER_IR_OPTIMIZEROPS_H

#include <mlir/IR/Builders.h>
#include <mlir/IR/BuiltinOps.h>
#include <mlir/IR/BuiltinTypes.h>

#define GET_OP_CLASSES
#include "toruslang/Dialect/Optimizer/IR/OptimizerOps.h.inc"

#endif
