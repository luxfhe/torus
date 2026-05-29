// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_Concrete_IR_ConcreteTYPES_H
#define TORUSLANG_DIALECT_Concrete_IR_ConcreteTYPES_H

#include "llvm/ADT/TypeSwitch.h"
#include <mlir/IR/BuiltinOps.h>
#include <mlir/IR/BuiltinTypes.h>
#include <mlir/IR/DialectImplementation.h>

#define GET_TYPEDEF_CLASSES
#include "toruslang/Dialect/Concrete/IR/ConcreteOpsTypes.h.inc"

#endif
