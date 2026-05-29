//===- FHELinalgTypes.td - FHELinalg dialect types ----------------*- tablegen -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef TORUSLANG_DIALECT_FHELinalg_IR_FHELinalg_TYPES
#define TORUSLANG_DIALECT_FHELinalg_IR_FHELinalg_TYPES

include "toruslang/Dialect/FHELinalg/IR/FHELinalgDialect.td"
include "mlir/IR/BuiltinTypes.td"
include "toruslang/Dialect/FHE/IR/FHETypes.td"

class FHELinalg_Type<string name, list<Trait> traits = []> :
  TypeDef<FHELinalg_Dialect, name, traits> { }

#endif
