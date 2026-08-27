// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_CLIENTLIB_REFACTORED_H
#define TORUSLANG_CLIENTLIB_REFACTORED_H

#include <cassert>
#include <cstdint>
#include <cstring>
#include <optional>
#include <string>
#include <variant>

#include "boost/outcome.h"
#include "torus-protocol.capnp.h"
#include "toruslang/Common/Csprng.h"
#include "toruslang/Common/Error.h"
#include "toruslang/Common/Keysets.h"
#include "toruslang/Common/Protocol.h"
#include "toruslang/Common/Transformers.h"
#include "toruslang/Common/Values.h"
#include "llvm/ADT/ArrayRef.h"

using toruslang::error::Result;
using toruslang::keysets::ClientKeyset;
using toruslang::transformers::InputTransformer;
using toruslang::transformers::OutputTransformer;
using toruslang::transformers::TransformerFactory;
using toruslang::values::TransportValue;
using toruslang::values::Value;

namespace toruslang {
namespace clientlib {



class ClientCircuit {

public:
  static Result<ClientCircuit>
  createEncrypted(const Message<torusprotocol::CircuitInfo> &info,
                  const ClientKeyset &keyset,
                  std::shared_ptr<csprng::EncryptionCSPRNG> csprng);

  static Result<ClientCircuit>
  createSimulated(const Message<torusprotocol::CircuitInfo> &info,
                  std::shared_ptr<csprng::EncryptionCSPRNG> csprng);

  Result<TransportValue> prepareInput(Value arg, size_t pos);

  Result<Value> processOutput(TransportValue result, size_t pos);

  Result<TransportValue> simulatePrepareInput(Value arg, size_t pos);

  Result<Value> simulateProcessOutput(TransportValue result, size_t pos);

  std::string getName();

  const Message<torusprotocol::CircuitInfo> &getCircuitInfo();

  bool isSimulated();

private:
  ClientCircuit() = delete;
  ClientCircuit(const Message<torusprotocol::CircuitInfo> &circuitInfo,
                std::vector<InputTransformer> inputTransformers,
                std::vector<OutputTransformer> outputTransformers,
                bool simulated)
      : circuitInfo(circuitInfo), inputTransformers(inputTransformers),
        outputTransformers(outputTransformers), simulated(simulated){};
  static Result<ClientCircuit>
  create(const Message<torusprotocol::CircuitInfo> &info,
         const ClientKeyset &keyset,
         std::shared_ptr<csprng::EncryptionCSPRNG> csprng, bool useSimulation);

private:
  Message<torusprotocol::CircuitInfo> circuitInfo;
  std::vector<InputTransformer> inputTransformers;
  std::vector<OutputTransformer> outputTransformers;
  bool simulated;
};

/// Contains all the context to generate inputs for a server call by the
/// server lib.
class ClientProgram {
public:
  /// Generates a fresh client program with fresh keyset on the first use.
  static Result<ClientProgram>
  createEncrypted(const Message<torusprotocol::ProgramInfo> &info,
                  const ClientKeyset &keyset,
                  std::shared_ptr<csprng::EncryptionCSPRNG> csprng);

  /// Generates a fresh client program with empty keyset for simulation.
  static Result<ClientProgram>
  createSimulated(const Message<torusprotocol::ProgramInfo> &info,
                  std::shared_ptr<csprng::EncryptionCSPRNG> csprng);

  /// Returns a reference to the named client circuit if it exists.
  Result<ClientCircuit> getClientCircuit(std::string circuitName) const;

private:
  ClientProgram() = default;

private:
  std::vector<ClientCircuit> circuits;
};

} // namespace clientlib
} // namespace toruslang

#endif
