//===- TFHETypes.td - TFHE dialect types ----------------*- tablegen -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef TORUSLANG_DIALECT_TFHE_IR_TFHE_TYPES
#define TORUSLANG_DIALECT_TFHE_IR_TFHE_TYPES

// TODO: MLWE / GSW

include "toruslang/Dialect/TFHE/IR/TFHEDialect.td"
include "mlir/IR/BuiltinTypes.td"

class TFHE_Type<string name, list<Trait> traits = []>
    : TypeDef<TFHE_Dialect, name, traits> {}

def TFHE_GLWECipherTextType
    : TFHE_Type<"GLWECipherText", [ MemRefElementTypeInterface ]> {
  let mnemonic = "glwe";

  let summary = "A GLWE ciphertext";

  let description = [{An GLWE cipher text}];

  let parameters = (ins
                    // The size of the mask
                    "mlir::toruslang::TFHE::GLWESecretKey"
                    : $key);

  let hasCustomAssemblyFormat = 1;

  let genVerifyDecl = true;
}

#endif
