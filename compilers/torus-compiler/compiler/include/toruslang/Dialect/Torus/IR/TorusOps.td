//===- TorusOps.td - Torus dialect ops ----------------*- tablegen -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef TORUSLANG_DIALECT_Torus_IR_Torus_OPS
#define TORUSLANG_DIALECT_Torus_IR_Torus_OPS

include "mlir/Interfaces/SideEffectInterfaces.td"
include "mlir/Interfaces/ControlFlowInterfaces.td"
include "mlir/IR/BuiltinTypes.td"
include "mlir/Dialect/MemRef/IR/MemRefBase.td"
include "mlir/Dialect/LLVMIR/LLVMOpBase.td"

include "toruslang/Dialect/Torus/IR/TorusDialect.td"
include "toruslang/Dialect/Torus/IR/TorusTypes.td"
include "toruslang/Dialect/RT/IR/RTDialect.td"
include "toruslang/Dialect/RT/IR/RTTypes.td"

def Torus_LweTensor : 1DTensorOf<[I64]>;
def Torus_LutTensor : 1DTensorOf<[I64]>;
def Torus_CrtLutsTensor : 2DTensorOf<[I64]>;
def Torus_CrtPlaintextTensor : 1DTensorOf<[I64]>;
def Torus_LweCRTTensor : 2DTensorOf<[I64]>;
def Torus_BatchLweTensor : 2DTensorOf<[I64]>;
def Torus_BatchPlaintextTensor : 1DTensorOf<[I64]>;
def Torus_BatchLutTensor : 2DTensorOf<[I64]>;

def Torus_LweBuffer : MemRefRankOf<[I64], [1]>;
def Torus_LutBuffer : MemRefRankOf<[I64], [1]>;
def Torus_CrtLutsBuffer : MemRefRankOf<[I64], [2]>;
def Torus_CrtPlaintextBuffer : MemRefRankOf<[I64], [1]>;
def Torus_LweCRTBuffer : MemRefRankOf<[I64], [2]>;
def Torus_BatchLweBuffer : MemRefRankOf<[I64], [2]>;
def Torus_BatchPlaintextBuffer : MemRefRankOf<[I64], [1]>;
def Torus_BatchLutBuffer : MemRefRankOf<[I64], [2]>;

class Torus_Op<string mnemonic, list<Trait> traits = []> :
    Op<Torus_Dialect, mnemonic, traits>;


def Torus_AddLweTensorOp : Torus_Op<"add_lwe_tensor", [Pure]> {
    let summary = "Returns the sum of 2 lwe ciphertexts";

    let arguments = (ins
        Torus_LweTensor:$lhs,
        Torus_LweTensor:$rhs
    );
    let results = (outs Torus_LweTensor:$result);
}

def Torus_AddLweBufferOp : Torus_Op<"add_lwe_buffer"> {
    let summary = "Returns the sum of 2 lwe ciphertexts";

    let arguments = (ins
        Torus_LweBuffer:$result,
        Torus_LweBuffer:$lhs,
        Torus_LweBuffer:$rhs
    );
}

def Torus_BatchedAddLweTensorOp : Torus_Op<"batched_add_lwe_tensor", [Pure]> {
    let summary = "Batched version of AddLweTensorOp, which performs the same operation on multiple elements";

    let arguments = (ins
        Torus_BatchLweTensor:$lhs,
        Torus_BatchLweTensor:$rhs
    );
    let results = (outs Torus_BatchLweTensor:$result);
}

def Torus_BatchedAddLweBufferOp : Torus_Op<"batched_add_lwe_buffer"> {
    let summary = "Batched version of AddLweBufferOp, which performs the same operation on multiple elements";

    let arguments = (ins
        Torus_BatchLweBuffer:$result,
        Torus_BatchLweBuffer:$lhs,
        Torus_BatchLweBuffer:$rhs
    );
}

def Torus_AddPlaintextLweTensorOp : Torus_Op<"add_plaintext_lwe_tensor", [Pure]> {
    let summary = "Returns the sum of a clear integer and an lwe ciphertext";

    let arguments = (ins Torus_LweTensor:$lhs, I64:$rhs);
    let results = (outs Torus_LweTensor:$result);
}

def Torus_AddPlaintextLweBufferOp : Torus_Op<"add_plaintext_lwe_buffer"> {
    let summary = "Returns the sum of a clear integer and an lwe ciphertext";

    let arguments = (ins
        Torus_LweBuffer:$result,
        Torus_LweBuffer:$lhs,
        I64:$rhs
    );
}

def Torus_BatchedAddPlaintextLweTensorOp : Torus_Op<"batched_add_plaintext_lwe_tensor", [Pure]> {
    let summary = "Batched version of AddPlaintextLweTensorOp, which performs the same operation on multiple elements";

    let arguments = (ins Torus_BatchLweTensor:$lhs, Torus_BatchPlaintextTensor:$rhs);
    let results = (outs Torus_BatchLweTensor:$result);
}

def Torus_BatchedAddPlaintextLweBufferOp : Torus_Op<"batched_add_plaintext_lwe_buffer"> {
    let summary = "Batched version of AddPlaintextLweBufferOp, which performs the same operation on multiple elements";

    let arguments = (ins
        Torus_BatchLweBuffer:$result,
        Torus_BatchLweBuffer:$lhs,
        Torus_BatchPlaintextBuffer:$rhs
    );
}

def Torus_BatchedAddPlaintextCstLweTensorOp : Torus_Op<"batched_add_plaintext_cst_lwe_tensor", [Pure]> {
    let summary = "Batched version of AddPlaintextLweTensorOp, which performs the same operation on multiple elements";

    let arguments = (ins Torus_BatchLweTensor:$lhs, I64:$rhs);
    let results = (outs Torus_BatchLweTensor:$result);
}

def Torus_BatchedAddPlaintextCstLweBufferOp : Torus_Op<"batched_add_plaintext_cst_lwe_buffer"> {
    let summary = "Batched version of AddPlaintextLweBufferOp, which performs the same operation on multiple elements";

    let arguments = (ins
        Torus_BatchLweBuffer:$result,
        Torus_BatchLweBuffer:$lhs,
        I64:$rhs
    );
}

def Torus_MulCleartextLweTensorOp : Torus_Op<"mul_cleartext_lwe_tensor", [Pure]> {
    let summary = "Returns the product of a clear integer and a lwe ciphertext";

    let arguments = (ins Torus_LweTensor:$lhs, I64:$rhs);
    let results = (outs Torus_LweTensor:$result);
}

def Torus_MulCleartextLweBufferOp : Torus_Op<"mul_cleartext_lwe_buffer"> {
    let summary = "Returns the product of a clear integer and a lwe ciphertext";

    let arguments = (ins
        Torus_LweBuffer:$result,
        Torus_LweBuffer:$lhs,
        I64:$rhs
    );
}

def Torus_BatchedMulCleartextLweTensorOp : Torus_Op<"batched_mul_cleartext_lwe_tensor", [Pure]> {
    let summary = "Batched version of MulCleartextLweTensorOp, which performs the same operation on multiple elements";

    let arguments = (ins Torus_BatchLweTensor:$lhs, Torus_BatchPlaintextTensor:$rhs);
    let results = (outs Torus_BatchLweTensor:$result);
}

def Torus_BatchedMulCleartextLweBufferOp : Torus_Op<"batched_mul_cleartext_lwe_buffer"> {
    let summary = "Batched version of MulCleartextLweBufferOp, which performs the same operation on multiple elements";

    let arguments = (ins
        Torus_BatchLweBuffer:$result,
        Torus_BatchLweBuffer:$lhs,
        Torus_BatchPlaintextBuffer:$rhs
    );
}

def Torus_BatchedMulCleartextCstLweTensorOp : Torus_Op<"batched_mul_cleartext_cst_lwe_tensor", [Pure]> {
    let summary = "Batched version of MulCleartextLweTensorOp, which performs the same operation on multiple elements";

    let arguments = (ins Torus_BatchLweTensor:$lhs, I64:$rhs);
    let results = (outs Torus_BatchLweTensor:$result);
}

def Torus_BatchedMulCleartextCstLweBufferOp : Torus_Op<"batched_mul_cleartext_cst_lwe_buffer"> {
    let summary = "Batched version of MulCleartextLweBufferOp, which performs the same operation on multiple elements";

    let arguments = (ins
        Torus_BatchLweBuffer:$result,
        Torus_BatchLweBuffer:$lhs,
        I64:$rhs
    );
}

def Torus_NegateLweTensorOp : Torus_Op<"negate_lwe_tensor", [Pure]> {
    let summary = "Negates an lwe ciphertext";

    let arguments = (ins Torus_LweTensor:$ciphertext);
    let results = (outs Torus_LweTensor:$result);
}

def Torus_NegateLweBufferOp : Torus_Op<"negate_lwe_buffer"> {
    let summary = "Negates an lwe ciphertext";

    let arguments = (ins
        Torus_LweBuffer:$result,
        Torus_LweBuffer:$ciphertext
    );
}

def Torus_BatchedNegateLweTensorOp : Torus_Op<"batched_negate_lwe_tensor", [Pure]> {
    let summary = "Batched version of NegateLweTensorOp, which performs the same operation on multiple elements";

    let arguments = (ins Torus_BatchLweTensor:$ciphertext);
    let results = (outs Torus_BatchLweTensor:$result);
}

def Torus_BatchedNegateLweBufferOp : Torus_Op<"batched_negate_lwe_buffer"> {
    let summary = "Batched version of NegateLweBufferOp, which performs the same operation on multiple elements";

    let arguments = (ins
        Torus_BatchLweBuffer:$result,
        Torus_BatchLweBuffer:$ciphertext
    );
}

def Torus_EncodeExpandLutForBootstrapTensorOp : Torus_Op<"encode_expand_lut_for_bootstrap_tensor", [Pure]> {
    let summary =
    "Encode and expand a lookup table so that it can be used for a bootstrap";

    let arguments = (ins
        Torus_LutTensor : $input_lookup_table,
        I32Attr: $polySize,
        I32Attr: $outputBits,
        BoolAttr: $isSigned
    );

    let results = (outs Torus_LutTensor : $result);
}

def Torus_EncodeExpandLutForBootstrapBufferOp : Torus_Op<"encode_expand_lut_for_bootstrap_buffer"> {
    let summary =
        "Encode and expand a lookup table so that it can be used for a bootstrap";

    let arguments = (ins
        Torus_LutBuffer: $result,
        Torus_LutBuffer: $input_lookup_table,
        I32Attr: $polySize,
        I32Attr: $outputBits,
        BoolAttr : $isSigned
    );
}

def Torus_EncodeLutForCrtWopPBSTensorOp : Torus_Op<"encode_lut_for_crt_woppbs_tensor", [Pure]> {
    let summary =
        "Encode and expand a lookup table so that it can be used for a wop pbs";

    let arguments = (ins
        Torus_LutTensor : $input_lookup_table,
        I64ArrayAttr: $crtDecomposition,
        I64ArrayAttr: $crtBits,
        I32Attr : $modulusProduct,
        BoolAttr: $isSigned
    );

    let results = (outs Torus_CrtLutsTensor : $result);
}

def Torus_EncodeLutForCrtWopPBSBufferOp : Torus_Op<"encode_lut_for_crt_woppbs_buffer"> {
    let summary =
        "Encode and expand a lookup table so that it can be used for a crt wop pbs";

    let arguments = (ins
        Torus_CrtLutsBuffer : $result,
        Torus_LutBuffer : $input_lookup_table,
        I64ArrayAttr: $crtDecomposition,
        I64ArrayAttr: $crtBits,
        I32Attr : $modulusProduct,
        BoolAttr: $isSigned
    );
}

def Torus_EncodePlaintextWithCrtTensorOp : Torus_Op<"encode_plaintext_with_crt_tensor", [Pure]> {
    let summary =
        "Encodes a plaintext by decomposing it on a crt basis";

    let arguments = (ins
        I64 : $input,
        I64ArrayAttr: $mods,
        I64Attr: $modsProd
    );

    let results = (outs Torus_CrtPlaintextTensor : $result);
}

def Torus_EncodePlaintextWithCrtBufferOp : Torus_Op<"encode_plaintext_with_crt_buffer"> {
    let summary =
        "Encodes a plaintext by decomposing it on a crt basis";

    let arguments = (ins
        Torus_CrtPlaintextBuffer: $result,
        I64 : $input,
        I64ArrayAttr: $mods,
        I64Attr: $modsProd
    );
}

def Torus_BootstrapLweTensorOp : Torus_Op<"bootstrap_lwe_tensor", [Pure]> {
    let summary = "Bootstraps an LWE ciphertext with a GLWE trivial encryption of the lookup table";

    let arguments = (ins
        Torus_LweTensor:$input_ciphertext,
        Torus_LweTensor:$lookup_table,
        I32Attr:$inputLweDim,
        I32Attr:$polySize,
        I32Attr:$level,
        I32Attr:$baseLog,
        I32Attr:$glweDimension,
        I32Attr:$bskIndex
    );
    let results = (outs Torus_LweTensor:$result);
}

def Torus_BootstrapLweBufferOp : Torus_Op<"bootstrap_lwe_buffer"> {
    let summary = "Bootstraps a LWE ciphertext with a GLWE trivial encryption of the lookup table";

    let arguments = (ins
        Torus_LweBuffer:$result,
        Torus_LweBuffer:$input_ciphertext,
        Torus_LutBuffer:$lookup_table,
        I32Attr:$inputLweDim,
        I32Attr:$polySize,
        I32Attr:$level,
        I32Attr:$baseLog,
        I32Attr:$glweDimension,
        I32Attr:$bskIndex
    );
}

def Torus_BatchedBootstrapLweTensorOp : Torus_Op<"batched_bootstrap_lwe_tensor", [Pure]> {
    let summary = "Batched version of BootstrapLweOp, which performs the same operation on multiple elements";

    let arguments = (ins
        Torus_BatchLweTensor:$input_ciphertext,
        Torus_LutTensor:$lookup_table,
        I32Attr:$inputLweDim,
        I32Attr:$polySize,
        I32Attr:$level,
        I32Attr:$baseLog,
        I32Attr:$glweDimension,
        I32Attr:$bskIndex
    );
    let results = (outs Torus_BatchLweTensor:$result);
}

def Torus_BatchedBootstrapLweBufferOp : Torus_Op<"batched_bootstrap_lwe_buffer"> {
    let summary = "Batched version of BootstrapLweOp, which performs the same operation on multiple elements";

    let arguments = (ins
        Torus_BatchLweBuffer:$result,
        Torus_BatchLweBuffer:$input_ciphertext,
        Torus_LutBuffer:$lookup_table,
        I32Attr:$inputLweDim,
        I32Attr:$polySize,
        I32Attr:$level,
        I32Attr:$baseLog,
        I32Attr:$glweDimension,
        I32Attr:$bskIndex
    );
}

def Torus_BatchedMappedBootstrapLweTensorOp : Torus_Op<"batched_mapped_bootstrap_lwe_tensor", [Pure]> {
    let summary = "Batched, mapped version of BootstrapLweOp, which performs the same operation on multiple elements";

    let arguments = (ins
        Torus_BatchLweTensor:$input_ciphertext,
        Torus_BatchLutTensor:$lookup_table_vector,
        I32Attr:$inputLweDim,
        I32Attr:$polySize,
        I32Attr:$level,
        I32Attr:$baseLog,
        I32Attr:$glweDimension,
        I32Attr:$bskIndex
    );
    let results = (outs Torus_BatchLweTensor:$result);
}

def Torus_BatchedMappedBootstrapLweBufferOp : Torus_Op<"batched_mapped_bootstrap_lwe_buffer"> {
    let summary = "Batched, mapped version of BootstrapLweOp, which performs the same operation on multiple elements";

    let arguments = (ins
        Torus_BatchLweBuffer:$result,
        Torus_BatchLweBuffer:$input_ciphertext,
        Torus_BatchLutBuffer:$lookup_table_vector,
        I32Attr:$inputLweDim,
        I32Attr:$polySize,
        I32Attr:$level,
        I32Attr:$baseLog,
        I32Attr:$glweDimension,
        I32Attr:$bskIndex
    );
}

def Torus_KeySwitchLweTensorOp : Torus_Op<"keyswitch_lwe_tensor", [Pure]> {
    let summary = "Performs a keyswitching operation on an LWE ciphertext";

    let arguments = (ins
        // LweKeySwitchKeyType:$keyswitch_key,
        Torus_LweTensor:$ciphertext,
        I32Attr:$level,
        I32Attr:$baseLog,
        I32Attr:$lwe_dim_in,
        I32Attr:$lwe_dim_out,
        I32Attr:$kskIndex
    );
    let results = (outs Torus_LweTensor:$result);
}

def Torus_KeySwitchLweBufferOp : Torus_Op<"keyswitch_lwe_buffer"> {
    let summary = "Performs a keyswitching operation on an LWE ciphertext";

    let arguments = (ins
        Torus_LweBuffer:$result,
        Torus_LweBuffer:$ciphertext,
        I32Attr:$level,
        I32Attr:$baseLog,
        I32Attr:$lwe_dim_in,
        I32Attr:$lwe_dim_out,
        I32Attr:$kskIndex
    );
}

def Torus_BatchedKeySwitchLweTensorOp : Torus_Op<"batched_keyswitch_lwe_tensor", [Pure]> {
    let summary = "Batched version of KeySwitchLweOp, which performs the same operation on multiple elements";

    let arguments = (ins
        // LweKeySwitchKeyType:$keyswitch_key,
        Torus_BatchLweTensor:$ciphertext,
        I32Attr:$level,
        I32Attr:$baseLog,
        I32Attr:$lwe_dim_in,
        I32Attr:$lwe_dim_out,
        I32Attr:$kskIndex
    );
    let results = (outs Torus_BatchLweTensor:$result);
}

def Torus_BatchedKeySwitchLweBufferOp : Torus_Op<"batched_keyswitch_lwe_buffer"> {
    let summary = "Batched version of KeySwitchLweOp, which performs the same operation on multiple elements";

    let arguments = (ins
        Torus_BatchLweBuffer:$result,
        Torus_BatchLweBuffer:$ciphertext,
        I32Attr:$level,
        I32Attr:$baseLog,
        I32Attr:$lwe_dim_in,
        I32Attr:$lwe_dim_out,
        I32Attr:$kskIndex
    );
}

def Torus_WopPBSCRTLweTensorOp : Torus_Op<"wop_pbs_crt_lwe_tensor", [Pure]> {
    let arguments = (ins
        Torus_LweCRTTensor:$ciphertext,
        Torus_CrtLutsTensor:$lookupTable,
        // Bootstrap parameters
        I32Attr : $bootstrapLevel,
        I32Attr : $bootstrapBaseLog,
        // Keyswitch parameters
        I32Attr : $keyswitchLevel,
        I32Attr : $keyswitchBaseLog,
        // Packing keyswitch key parameters
        I32Attr : $packingKeySwitchInputLweDimension,
        I32Attr : $packingKeySwitchoutputPolynomialSize,
        I32Attr : $packingKeySwitchLevel,
        I32Attr : $packingKeySwitchBaseLog,
        // Circuit bootstrap parameters
        I32Attr : $circuitBootstrapLevel,
        I32Attr : $circuitBootstrapBaseLog,
        I64ArrayAttr:$crtDecomposition,
        // Key indices
        I32Attr:$kskIndex,
        I32Attr:$bskIndex,
        I32Attr:$pkskIndex
    );
    let results = (outs Torus_LweCRTTensor:$result);
}

def Torus_WopPBSCRTLweBufferOp : Torus_Op<"wop_pbs_crt_lwe_buffer"> {
    let arguments = (ins
        Torus_LweCRTBuffer:$result,
        Torus_LweCRTBuffer:$ciphertext,
        Torus_CrtLutsBuffer:$lookup_table,
        // Bootstrap parameters
        I32Attr : $bootstrapLevel,
        I32Attr : $bootstrapBaseLog,
        // Keyswitch parameters
        I32Attr : $keyswitchLevel,
        I32Attr : $keyswitchBaseLog,
        // Packing keyswitch key parameters
        I32Attr : $packingKeySwitchInputLweDimension,
        I32Attr : $packingKeySwitchoutputPolynomialSize,
        I32Attr : $packingKeySwitchLevel,
        I32Attr : $packingKeySwitchBaseLog,
        // Circuit bootstrap parameters
        I32Attr : $circuitBootstrapLevel,
        I32Attr : $circuitBootstrapBaseLog,
        I64ArrayAttr:$crtDecomposition,
        // Key indices
        I32Attr:$kskIndex,
        I32Attr:$bskIndex,
        I32Attr:$pkskIndex
    );
}

#endif
