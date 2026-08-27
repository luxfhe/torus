// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include <cassert>
#include <cstdint>
#include <cstring>
#include <functional>
#include <numeric>
#include <optional>
#include <string>
#include <variant>

#include "boost/outcome.h"
#include "capnp/common.h"
#include "torus-cpu.h"
#include "torus-protocol.capnp.h"
#include "toruslang/ClientLib/ClientLib.h"
#include "toruslang/Common/Csprng.h"
#include "toruslang/Common/Error.h"
#include "toruslang/Common/Keysets.h"
#include "toruslang/Common/Protocol.h"
#include "toruslang/Common/Transformers.h"
#include "toruslang/Common/Values.h"

using toruslang::error::Result;
using toruslang::keysets::ClientKeyset;
using toruslang::transformers::InputTransformer;
using toruslang::transformers::OutputTransformer;
using toruslang::transformers::TransformerFactory;
using toruslang::values::TransportValue;
using toruslang::values::Value;

namespace toruslang {
namespace clientlib {

bool ClientCircuit::isSimulated() { return simulated; }

Result<ClientCircuit>
ClientCircuit::create(const Message<torusprotocol::CircuitInfo> &info,
                      const ClientKeyset &keyset,
                      std::shared_ptr<csprng::EncryptionCSPRNG> csprng,
                      bool useSimulation) {

  auto inputTransformers = std::vector<InputTransformer>();

  for (auto gateInfo : info.asReader().getInputs()) {
    InputTransformer transformer;
    if (gateInfo.getTypeInfo().hasIndex()) {
      OUTCOME_TRY(transformer,
                  TransformerFactory::getIndexInputTransformer(
                      (Message<torusprotocol::GateInfo>)gateInfo));
    } else if (gateInfo.getTypeInfo().hasPlaintext()) {
      OUTCOME_TRY(transformer,
                  TransformerFactory::getPlaintextInputTransformer(
                      (Message<torusprotocol::GateInfo>)gateInfo));
    } else if (gateInfo.getTypeInfo().hasLweCiphertext()) {
      OUTCOME_TRY(transformer,
                  TransformerFactory::getLweCiphertextInputTransformer(
                      keyset, (Message<torusprotocol::GateInfo>)gateInfo,
                      csprng, useSimulation));
    } else {
      return StringError("Malformed input gate info.");
    }
    inputTransformers.push_back(transformer);
  }

  auto outputTransformers = std::vector<OutputTransformer>();

  for (auto gateInfo : info.asReader().getOutputs()) {
    OutputTransformer transformer;
    if (gateInfo.getTypeInfo().hasIndex()) {
      OUTCOME_TRY(transformer,
                  TransformerFactory::getIndexOutputTransformer(
                      (Message<torusprotocol::GateInfo>)gateInfo));
    } else if (gateInfo.getTypeInfo().hasPlaintext()) {
      OUTCOME_TRY(transformer,
                  TransformerFactory::getPlaintextOutputTransformer(
                      (Message<torusprotocol::GateInfo>)gateInfo));
    } else if (gateInfo.getTypeInfo().hasLweCiphertext()) {
      OUTCOME_TRY(transformer,
                  TransformerFactory::getLweCiphertextOutputTransformer(
                      keyset, (Message<torusprotocol::GateInfo>)gateInfo,
                      useSimulation));
    } else {
      return StringError("Malformed output gate info.");
    }
    outputTransformers.push_back(transformer);
  }

  return ClientCircuit(info, inputTransformers, outputTransformers,
                       useSimulation);
}

Result<ClientCircuit> ClientCircuit::createEncrypted(
    const Message<torusprotocol::CircuitInfo> &info,
    const ClientKeyset &keyset,
    std::shared_ptr<csprng::EncryptionCSPRNG> csprng) {
  return ClientCircuit::create(info, keyset, csprng, false);
}

Result<ClientCircuit> ClientCircuit::createSimulated(
    const Message<torusprotocol::CircuitInfo> &info,
    std::shared_ptr<csprng::EncryptionCSPRNG> csprng) {
  return ClientCircuit::create(info, ClientKeyset(), csprng, true);
}

Result<TransportValue> ClientCircuit::prepareInput(Value arg, size_t pos) {
  if (simulated) {
    return StringError("Called prepareInput on simulated client circuit.");
  }
  if (pos >= inputTransformers.size()) {
    return StringError("Tried to prepare a Value for incorrect position.");
  }
  return inputTransformers[pos](arg);
}

Result<Value> ClientCircuit::processOutput(TransportValue result, size_t pos) {
  if (simulated) {
    return StringError("Called processOutput on simulated client circuit.");
  }
  if (pos >= outputTransformers.size()) {
    return StringError(
        "Tried to process a TransportValue for incorrect position.");
  }
  return outputTransformers[pos](result);
}

Result<TransportValue> ClientCircuit::simulatePrepareInput(Value arg,
                                                           size_t pos) {
  if (!simulated) {
    return StringError(
        "Called simulatePrepareInput on encrypted client circuit.");
  }
  if (pos >= inputTransformers.size()) {
    return StringError("Tried to prepare a Value for incorrect position.");
  }
  return inputTransformers[pos](arg);
}

Result<Value> ClientCircuit::simulateProcessOutput(TransportValue result,
                                                   size_t pos) {
  if (!simulated) {
    return StringError(
        "Called simulateProcessOutput on encrypted client circuit.");
  }
  if (pos >= outputTransformers.size()) {
    return StringError(
        "Tried to process a TransportValue for incorrect position.");
  }
  return outputTransformers[pos](result);
}

std::string ClientCircuit::getName() {
  return circuitInfo.asReader().getName();
}

const Message<torusprotocol::CircuitInfo> &ClientCircuit::getCircuitInfo() {
  return circuitInfo;
}

Result<ClientProgram> ClientProgram::createEncrypted(
    const Message<torusprotocol::ProgramInfo> &info,
    const ClientKeyset &keyset,
    std::shared_ptr<csprng::EncryptionCSPRNG> csprng) {
  ClientProgram output;
  for (auto circuitInfo : info.asReader().getCircuits()) {
    OUTCOME_TRY(const ClientCircuit clientCircuit,
                ClientCircuit::createEncrypted(
                    (Message<torusprotocol::CircuitInfo>)circuitInfo, keyset,
                    csprng));
    output.circuits.push_back(clientCircuit);
  }
  return output;
}

Result<ClientProgram> ClientProgram::createSimulated(
    const Message<torusprotocol::ProgramInfo> &info,
    std::shared_ptr<csprng::EncryptionCSPRNG> csprng) {
  ClientProgram output;
  for (auto circuitInfo : info.asReader().getCircuits()) {
    OUTCOME_TRY(
        const ClientCircuit clientCircuit,
        ClientCircuit::createSimulated(
            (Message<torusprotocol::CircuitInfo>)circuitInfo, csprng));
    output.circuits.push_back(clientCircuit);
  }
  return output;
}

Result<ClientCircuit>
ClientProgram::getClientCircuit(std::string circuitName) const {
  for (auto circuit : circuits) {
    if (circuit.getName() == circuitName) {
      return circuit;
    }
  }
  return StringError("Tried to get unknown client circuit: `" + circuitName +
                     "`");
}



} // namespace clientlib
} // namespace toruslang
