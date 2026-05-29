// Part of the Concrete Compiler Project, under the BSD3 License with Zama
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_Concrete_Concrete_OPS_H
#define TORUSLANG_DIALECT_Concrete_Concrete_OPS_H

#include <mlir/IR/Builders.h>
#include <mlir/IR/BuiltinOps.h>
#include <mlir/IR/BuiltinTypes.h>
#include <mlir/Interfaces/ControlFlowInterfaces.h>
#include <mlir/Interfaces/SideEffectInterfaces.h>

#include "toruslang/Dialect/Concrete/IR/ConcreteTypes.h"

#define GET_OP_CLASSES
#include "toruslang/Dialect/Concrete/IR/ConcreteOps.h.inc"

#endif
