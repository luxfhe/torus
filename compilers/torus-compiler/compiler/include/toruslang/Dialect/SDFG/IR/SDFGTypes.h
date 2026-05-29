// Part of the Concrete Compiler Project, under the BSD3 License with Zama
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_SDFG_IR_SDFGTYPES_H
#define TORUSLANG_DIALECT_SDFG_IR_SDFGTYPES_H

#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/DialectImplementation.h"
#include "llvm/ADT/TypeSwitch.h"

#define GET_TYPEDEF_CLASSES
#include "toruslang/Dialect/SDFG/IR/SDFGTypes.h.inc"

#endif
