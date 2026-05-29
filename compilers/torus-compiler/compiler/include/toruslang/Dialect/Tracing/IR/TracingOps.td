#ifndef TORUSLANG_DIALECT_TRACING_IR_TRACING_OPS
#define TORUSLANG_DIALECT_TRACING_IR_TRACING_OPS

include "mlir/Interfaces/SideEffectInterfaces.td"
include "mlir/Interfaces/ControlFlowInterfaces.td"

include "toruslang/Dialect/Tracing/IR/TracingDialect.td"
include "toruslang/Dialect/FHE/IR/FHETypes.td"
include "toruslang/Dialect/TFHE/IR/TFHETypes.td"
include "toruslang/Dialect/Concrete/IR/ConcreteTypes.td"

class Tracing_Op<string mnemonic, list<Trait> traits = []>
    : Op<Tracing_Dialect, mnemonic, traits>;

def Tracing_TraceCiphertextOp : Tracing_Op<"trace_ciphertext"> {
  let summary = "Prints a ciphertext.";

  let arguments = (ins
        Type<Or<[
            FHE_EncryptedUnsignedIntegerType.predicate,
            FHE_EncryptedSignedIntegerType.predicate,
            TFHE_GLWECipherTextType.predicate,
            1DTensorOf<[I64]>.predicate,
            MemRefRankOf<[I64], [1]>.predicate
        ]>>: $ciphertext,
        OptionalAttr<StrAttr>: $msg,
        OptionalAttr<I32Attr>: $nmsb
    );
}

def Tracing_TracePlaintextOp : Tracing_Op<"trace_plaintext"> {
  let summary = "Prints a plaintext.";

  let arguments = (ins
        AnyInteger: $plaintext,
        OptionalAttr<StrAttr>: $msg,
        OptionalAttr<I32Attr>: $nmsb
    );
}

def Tracing_TraceMessageOp : Tracing_Op<"trace_message"> {
  let summary = "Prints a message.";

  let arguments = (ins OptionalAttr<StrAttr> : $msg);
}

#endif
