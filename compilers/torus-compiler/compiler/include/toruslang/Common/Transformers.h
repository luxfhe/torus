// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_COMMON_TRANSFORMERS_H
#define TORUSLANG_COMMON_TRANSFORMERS_H

#include "torus-protocol.capnp.h"
#include "toruslang/Common/Error.h"
#include "toruslang/Common/Keysets.h"
#include "toruslang/Common/Values.h"
#include <memory>
#include <stdlib.h>

using toruslang::error::Result;
using toruslang::keysets::ClientKeyset;
using toruslang::values::Tensor;
using toruslang::values::TransportValue;
using toruslang::values::Value;

/// \brief simulate the encryption of a value by adding noise
///
/// \param message encoded message to encrypt
/// \param lwe_dim
/// \param csprng used to generate noise during encryption
/// \return noisy plaintext
uint64_t sim_encrypt_lwe_u64(uint64_t message, uint32_t lwe_dim,
                             Csprng *encrypt_csprng);

namespace toruslang {
namespace transformers {

/// A type for input transformers, that is, functions running on the client
/// side, that prepare a Value to be sent to the server as a TransportValue.
typedef std::function<Result<TransportValue>(Value)> InputTransformer;

/// A type for output transformers, that is, functions running on the client
/// side, that process a TransportValue fetched from the server to be used as a
/// Value.
typedef std::function<Result<Value>(TransportValue)> OutputTransformer;

/// A type for arguments transformers, that is, functions running on the server
/// side, that transform a TransportValue fetched from the client, to be used as
/// argument in a circuit call.
typedef std::function<Result<Value>(TransportValue)> ArgTransformer;

/// A type for return transformers, that is, functions running on the server
/// side, that transform a value returned from circuit call into a
/// TransportValue to be sent to the client.
typedef std::function<Result<TransportValue>(Value)> ReturnTransformer;

/// A factory static class that generates transformers.
class TransformerFactory {
public:
  static Result<InputTransformer>
  getIndexInputTransformer(Message<torusprotocol::GateInfo> gateInfo);

  static Result<OutputTransformer>
  getIndexOutputTransformer(Message<torusprotocol::GateInfo> gateInfo);

  static Result<ArgTransformer>
  getIndexArgTransformer(Message<torusprotocol::GateInfo> gateInfo);

  static Result<ReturnTransformer>
  getIndexReturnTransformer(Message<torusprotocol::GateInfo> gateInfo);

  static Result<InputTransformer>
  getPlaintextInputTransformer(Message<torusprotocol::GateInfo> gateInfo);

  static Result<OutputTransformer>
  getPlaintextOutputTransformer(Message<torusprotocol::GateInfo> gateInfo);

  static Result<ArgTransformer>
  getPlaintextArgTransformer(Message<torusprotocol::GateInfo> gateInfo);

  static Result<ReturnTransformer>
  getPlaintextReturnTransformer(Message<torusprotocol::GateInfo> gateInfo);

  static Result<InputTransformer> getLweCiphertextInputTransformer(
      ClientKeyset keyset, Message<torusprotocol::GateInfo> gateInfo,
      std::shared_ptr<toruslang::csprng::EncryptionCSPRNG> csprng,
      bool useSimulation);

  static Result<OutputTransformer> getLweCiphertextOutputTransformer(
      ClientKeyset keyset, Message<torusprotocol::GateInfo> gateInfo,
      bool useSimulation);

  static Result<ArgTransformer>
  getLweCiphertextArgTransformer(Message<torusprotocol::GateInfo> gateInfo,
                                 bool useSimulation);

  static Result<ReturnTransformer> getLweCiphertextReturnTransformer(
      Message<torusprotocol::GateInfo> gateInfo, bool useSimulation);
};

} // namespace transformers
} // namespace toruslang

#endif
