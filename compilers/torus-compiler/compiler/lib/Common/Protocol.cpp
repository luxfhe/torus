// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "toruslang/Common/Protocol.h"
#include "torus-protocol.capnp.h"
#include "toruslang/Common/Error.h"
#include "llvm/ADT/Hashing.h"
#include <memory>
#include <stdlib.h>

namespace toruslang {
namespace protocol {

/// Helper function turning a protocol `Shape` object into a vector of
/// dimensions.
std::vector<size_t>
protoShapeToDimensions(const Message<torusprotocol::Shape> &shape) {
  return protoShapeToDimensions(shape.asReader());
}

std::vector<size_t>
protoShapeToDimensions(torusprotocol::Shape::Reader reader) {
  auto output = std::vector<size_t>();
  for (auto dim : reader.getDimensions()) {
    output.push_back(dim);
  }
  return output;
}

/// Helper function turning a protocol `Shape` object into a vector of
/// dimensions.
Message<torusprotocol::Shape>
dimensionsToProtoShape(const std::vector<size_t> &input) {
  auto output = Message<torusprotocol::Shape>();
  auto dimensions = output.asBuilder().initDimensions(input.size());
  for (size_t i = 0; i < input.size(); i++) {
    dimensions.set(i, input[i]);
  }
  return output;
}

template <typename Message> size_t hashMessage(Message &mess) {
  return llvm::hash_value(MessageToJSONString(mess));
}

} // namespace protocol
} // namespace toruslang
