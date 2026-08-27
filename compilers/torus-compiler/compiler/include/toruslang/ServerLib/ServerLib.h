// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_SERVERLIB_SERVER_LAMBDA_H
#define TORUSLANG_SERVERLIB_SERVER_LAMBDA_H

#include "boost/outcome.h"
#include "torus-protocol.capnp.h"
#include "toruslang/Common/Error.h"
#include "toruslang/Common/Keysets.h"
#include "toruslang/Common/Protocol.h"
#include "toruslang/Common/Transformers.h"
#include "toruslang/Common/Values.h"
#include "llvm/ADT/ArrayRef.h"
#include <cassert>
#include <dlfcn.h>
#include <functional>
#include <memory>
#include <vector>

using toruslang::keysets::ServerKeyset;
using toruslang::transformers::ArgTransformer;
using toruslang::transformers::ReturnTransformer;
using toruslang::transformers::TransformerFactory;
using toruslang::values::Value;

namespace toruslang {
namespace serverlib {

/// A smart pointer to a dynamic module.
class DynamicModule {
  friend class ServerCircuit;

public:
  ~DynamicModule();
  static Result<std::shared_ptr<DynamicModule>>
  open(const std::string &outputPath);

private:
  void *libraryHandle;
};

class ServerCircuit {
  friend class ServerProgram;

public:
  static Result<ServerCircuit>
  fromFnPtr(const Message<torusprotocol::CircuitInfo> &circuitInfo,
            void (*func)(void *...), bool useSimulation);

  /// Call the circuit with public arguments.
  Result<std::vector<TransportValue>>
  call(const ServerKeyset &serverKeyset,
       const std::vector<TransportValue> &args);

  /// Simulate the circuit with public arguments.
  Result<std::vector<TransportValue>>
  simulate(const std::vector<TransportValue> &args);

  /// Returns the name of this circuit.
  std::string getName();

private:
  ServerCircuit() = default;

  static Result<ServerCircuit>
  fromDynamicModule(const Message<torusprotocol::CircuitInfo> &circuitInfo,
                    std::shared_ptr<DynamicModule> dynamicModule,
                    bool useSimulation);

  void invoke(const ServerKeyset &serverKeyset);

  Message<torusprotocol::CircuitInfo> circuitInfo;
  bool useSimulation;
  void (*func)(void *...);
  std::shared_ptr<DynamicModule> dynamicModule;
  std::vector<ArgTransformer> argTransformers;
  std::vector<ReturnTransformer> returnTransformers;
  std::vector<Value> argsBuffer;
  std::vector<Value> returnsBuffer;
  std::vector<size_t> argDescriptorSizes;
  std::vector<size_t> returnDescriptorSizes;
  size_t argRawSize;
  size_t returnRawSize;
};

/// ServerProgram contains multiple
class ServerProgram {
public:
  /// Loads a server program from a shared lib path essentially.
  static Result<ServerProgram>
  load(const Message<torusprotocol::ProgramInfo> &programInfo,
       const std::string &outputPath, bool useSimulation);

  Result<ServerCircuit> getServerCircuit(const std::string &circuitName);

private:
  ServerProgram() = default;

  std::vector<ServerCircuit> serverCircuits;
};

} // namespace serverlib
} // namespace toruslang

#endif
