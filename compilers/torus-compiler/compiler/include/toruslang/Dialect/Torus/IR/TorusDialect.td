//===- TorusDialect.td - Torus dialect ----------------*- tablegen -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef TORUSLANG_DIALECT_Torus_IR_Torus_DIALECT
#define TORUSLANG_DIALECT_Torus_IR_Torus_DIALECT

include "mlir/IR/OpBase.td"

def Torus_Dialect : Dialect {
  let name = "Torus";
  let summary = "Low Level Fully Homomorphic Encryption dialect";
  let description = [{
    A dialect for representation of low level operation on fully homomorphic ciphertext.
  }];
  let cppNamespace = "::mlir::toruslang::Torus";
  let useDefaultTypePrinterParser = 1;
}

#endif
