// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifdef TORUSLANG_DATAFLOW_EXECUTION_ENABLED

#include "toruslang/Runtime/key_manager.hpp"
#include "toruslang/Common/Keysets.h"
#include "toruslang/Runtime/context.h"

namespace mlir {
namespace toruslang {
namespace dfr {

RuntimeContextManager *_dfr_node_level_runtime_context_manager;

KeyWrapper<LweKeyswitchKey> getKsk(size_t keyId) {
  return KeyWrapper<LweKeyswitchKey>(std::vector<LweKeyswitchKey>{
      _dfr_node_level_runtime_context_manager->context->getKeys()
          .lweKeyswitchKeys[keyId]});
}

KeyWrapper<LweBootstrapKey> getBsk(size_t keyId) {
  return KeyWrapper<LweBootstrapKey>(std::vector<LweBootstrapKey>{
      _dfr_node_level_runtime_context_manager->context->getKeys()
          .lweBootstrapKeys[keyId]});
}

KeyWrapper<PackingKeyswitchKey> getPKsk(size_t keyId) {
  return KeyWrapper<PackingKeyswitchKey>(std::vector<PackingKeyswitchKey>{
      _dfr_node_level_runtime_context_manager->context->getKeys()
          .packingKeyswitchKeys[keyId]});
}

} // namespace dfr
} // namespace toruslang
} // namespace mlir
#endif
