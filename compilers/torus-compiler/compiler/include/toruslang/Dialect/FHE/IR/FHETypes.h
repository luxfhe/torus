// Part of the Concrete Compiler Project, under the BSD3 License with Zama
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_FHE_IR_FHETYPES_H
#define TORUSLANG_DIALECT_FHE_IR_FHETYPES_H

#include "llvm/ADT/TypeSwitch.h"
#include <mlir/IR/BuiltinOps.h>
#include <mlir/IR/BuiltinTypes.h>
#include <mlir/IR/DialectImplementation.h>

#include <mlir/Dialect/Arith/IR/Arith.h>

#include "toruslang/Dialect/FHE/Interfaces/FHEInterfaces.h"

#define GET_TYPEDEF_CLASSES
#include "toruslang/Dialect/FHE/IR/FHEOpsTypes.h.inc"

#endif
