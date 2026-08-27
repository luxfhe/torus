//===- TorusTypes.td - Torus dialect types ----------------*- tablegen -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef TORUSLANG_DIALECT_Torus_IR_Torus_TYPES
#define TORUSLANG_DIALECT_Torus_IR_Torus_TYPES

include "mlir/IR/BuiltinTypes.td"

include "toruslang/Dialect/Torus/IR/TorusDialect.td"

class Torus_Type<string name, list<Trait> traits = []> : TypeDef<Torus_Dialect, name, traits> { }

def Torus_Context : Torus_Type<"Context"> {
    let mnemonic = "context";

    let summary = "A runtime context";

    let description = [{
       An abstract runtime context to pass contextual value, like public keys, ...
    }];
}

#endif
