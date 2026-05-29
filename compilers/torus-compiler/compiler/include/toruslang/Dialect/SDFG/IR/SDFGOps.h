// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_SDFG_IR_SDFGOPS_H
#define TORUSLANG_DIALECT_SDFG_IR_SDFGOPS_H

#include "mlir/IR/Dialect.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"

#include "toruslang/Dialect/SDFG/IR/SDFGEnums.h.inc"
#include "toruslang/Dialect/SDFG/IR/SDFGTypes.h"

#define GET_ATTRDEF_CLASSES
#include "toruslang/Dialect/SDFG/IR/SDFGAttributes.h.inc"

#define GET_OP_CLASSES
#include "toruslang/Dialect/SDFG/IR/SDFGOps.h.inc"

#endif
