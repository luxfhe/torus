// Part of the Concrete Compiler Project, under the BSD3 License with Zama
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_SUPPORT_PROGRAMINFOGENERATION_H_
#define TORUSLANG_SUPPORT_PROGRAMINFOGENERATION_H_

#include "torus-protocol.capnp.h"
#include "toruslang/Common/Protocol.h"
#include "toruslang/Support/Encodings.h"
#include "toruslang/Support/V0Parameters.h"
#include "mlir/Dialect/LLVMIR/LLVMTypes.h"
#include "mlir/IR/BuiltinOps.h"
#include <memory>

using toruslang::protocol::Message;

namespace mlir {
namespace toruslang {

llvm::Expected<Message<concreteprotocol::ProgramInfo>>
createProgramInfoFromTfheDialect(
    mlir::ModuleOp module, int bitsOfSecurity,
    const Message<concreteprotocol::ProgramEncodingInfo> &encodings,
    bool compressEvaluationKeys, bool compressInputCiphertexts);

} // namespace toruslang
} // namespace mlir

#endif
