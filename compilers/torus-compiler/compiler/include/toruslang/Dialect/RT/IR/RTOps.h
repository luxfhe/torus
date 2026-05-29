// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_RT_IR_RTOPS_H
#define TORUSLANG_DIALECT_RT_IR_RTOPS_H

#include <mlir/Dialect/Bufferization/IR/AllocationOpInterface.h>
#include <mlir/Dialect/Bufferization/IR/BufferizableOpInterface.h>
#include <mlir/IR/BuiltinOps.h>
#include <mlir/IR/BuiltinTypes.h>
#include <mlir/Interfaces/ControlFlowInterfaces.h>
#include <mlir/Interfaces/DataLayoutInterfaces.h>
#include <mlir/Interfaces/SideEffectInterfaces.h>

#include "toruslang/Dialect/RT/IR/RTTypes.h"

#define GET_OP_CLASSES
#include "toruslang/Dialect/RT/IR/RTOps.h.inc"

#endif
