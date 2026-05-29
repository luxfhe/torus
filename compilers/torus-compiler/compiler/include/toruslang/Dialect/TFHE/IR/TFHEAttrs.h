// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_TFHE_IR_TFHEATTRS_H
#define TORUSLANG_DIALECT_TFHE_IR_TFHEATTRS_H

#include "toruslang/Dialect/TFHE/IR/TFHEParameters.h"
#include "llvm/ADT/TypeSwitch.h"
#include <mlir/Dialect/Func/IR/FuncOps.h>
#include <mlir/IR/BuiltinOps.h>
#include <mlir/IR/BuiltinTypes.h>
#include <mlir/IR/DialectImplementation.h>

#define GET_ATTRDEF_CLASSES
#include "toruslang/Dialect/TFHE/IR/TFHEAttrs.h.inc"

#endif
