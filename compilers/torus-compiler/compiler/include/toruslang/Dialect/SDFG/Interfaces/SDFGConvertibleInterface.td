#ifndef TORUSLANG_DIALECT_SDFG_INTERFACES_SDFGCONVERTIBLEINTERFACE
#define TORUSLANG_DIALECT_SDFG_INTERFACES_SDFGCONVERTIBLEINTERFACE

include "mlir/IR/OpBase.td"

def SDFG_SDFGConvertibleOpInterface : OpInterface<"SDFGConvertibleOpInterface"> {
  let description = [{
      Interface for operations processing a scalar that can be batched
    if invoked multiple times with different, independent operands.
  }];
  let cppNamespace = "::mlir::toruslang::SDFG";

  let methods = [
    InterfaceMethod<[{
        Create the associated operation and return it as a value.
      }],
      /*retTy=*/"::mlir::toruslang::SDFG::MakeProcess",
      /*methodName=*/"convert",
      /*args=*/(ins "::mlir::ImplicitLocOpBuilder&":$builder,
                    "::mlir::Value":$dfg,
                    "::mlir::ValueRange":$inStreams,
                    "::mlir::ValueRange":$outStreams),
      /*methodBody=*/"",
      /*defaultImplementation=*/[{
        llvm_unreachable("convert not implemented");
      }]
    >
  ];
}

#endif // TORUSLANG_DIALECT_SDFG_INTERFACES_SDFGCONVERTIBLEINTERFACE
