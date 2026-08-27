// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_Torus_Torus_OPS_H
#define TORUSLANG_DIALECT_Torus_Torus_OPS_H

#include <mlir/IR/Builders.h>
#include <mlir/IR/BuiltinOps.h>
#include <mlir/IR/BuiltinTypes.h>
#include <mlir/Interfaces/ControlFlowInterfaces.h>
#include <mlir/Interfaces/SideEffectInterfaces.h>

#include "toruslang/Dialect/Torus/IR/TorusTypes.h"

#define GET_OP_CLASSES
#include "toruslang/Dialect/Torus/IR/TorusOps.h.inc"

#endif
