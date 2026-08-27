// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_SUPPORT_ENCODINGS_H_
#define TORUSLANG_SUPPORT_ENCODINGS_H_

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "boost/outcome.h"
#include <llvm/ADT/Optional.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/JSON.h>
#include <llvm/Support/raw_ostream.h>

#include <mlir/Dialect/Func/IR/FuncOps.h>
#include <mlir/Dialect/LLVMIR/LLVMDialect.h>

#include "capnp/message.h"
#include "torus-protocol.capnp.h"
#include "toruslang/Common/Error.h"
#include "toruslang/Common/Protocol.h"
#include "toruslang/Conversion/Utils/GlobalFHEContext.h"
#include "toruslang/Dialect/FHE/IR/FHETypes.h"

using toruslang::protocol::Message;

namespace mlir {
namespace toruslang {
namespace encodings {

llvm::Expected<Message<torusprotocol::ProgramEncodingInfo>>
getProgramEncoding(mlir::ModuleOp module);

void setProgramEncodingModes(
    Message<torusprotocol::ProgramEncodingInfo> &info,
    std::optional<
        Message<torusprotocol::IntegerCiphertextEncodingInfo::ChunkedMode>>
        maybeChunk,
    std::optional<V0FHEContext> maybeFheContext);

} // namespace encodings
} // namespace toruslang
} // namespace mlir

#endif
