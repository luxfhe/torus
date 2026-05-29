// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_TFHE_IR_TFHEOPS_H
#define TORUSLANG_DIALECT_TFHE_IR_TFHEOPS_H

#include <mlir/IR/Builders.h>
#include <mlir/IR/BuiltinOps.h>
#include <mlir/IR/BuiltinTypes.h>
#include <mlir/Interfaces/ControlFlowInterfaces.h>
#include <mlir/Interfaces/SideEffectInterfaces.h>

#include "toruslang/Dialect/TFHE/IR/TFHEAttrs.h"
#include "toruslang/Dialect/TFHE/IR/TFHETypes.h"
#include "toruslang/Interfaces/BatchableInterface.h"

#define GET_OP_CLASSES
#include "toruslang/Dialect/TFHE/IR/TFHEOps.h.inc"

#endif
