// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_COMMON_KEYSETS_H
#define TORUSLANG_COMMON_KEYSETS_H

#include "torus-optimizer.hpp"
#include "torus-protocol.capnp.h"
#include "toruslang/Common/Csprng.h"
#include "toruslang/Common/Error.h"
#include "toruslang/Common/Keys.h"
#include <functional>
#include <map>
#include <memory>
#include <stdlib.h>
#include <string>

using toruslang::error::Result;
using toruslang::error::StringError;
using toruslang::keys::LweBootstrapKey;
using toruslang::keys::LweKeyswitchKey;
using toruslang::keys::LweSecretKey;
using toruslang::keys::PackingKeyswitchKey;

namespace toruslang {
namespace keysets {

struct ClientKeyset {
  std::vector<LweSecretKey> lweSecretKeys;

  static ClientKeyset
  fromProto(const Message<torusprotocol::ClientKeyset> &proto);

  static ClientKeyset fromProto(torusprotocol::ClientKeyset::Reader reader);

  Message<torusprotocol::ClientKeyset> toProto() const;
};

struct ServerKeyset {
  std::vector<LweBootstrapKey> lweBootstrapKeys;
  std::vector<LweKeyswitchKey> lweKeyswitchKeys;
  std::vector<PackingKeyswitchKey> packingKeyswitchKeys;

  static ServerKeyset
  fromProto(const Message<torusprotocol::ServerKeyset> &proto);
  static ServerKeyset fromProto(torusprotocol::ServerKeyset::Reader reader);

  Message<torusprotocol::ServerKeyset> toProto() const;
};

struct Keyset {
  ServerKeyset server;
  ClientKeyset client;

  Keyset(){};

  /// @brief Generates a keyset from infos.
  ///
  /// This can be a fresh keyset if no key is specified in `lweSecretKeys`.
  /// Otherwise those keys are set first, then the rest of the key will be
  /// generated.
  ///
  /// @param info
  /// @param secretCsprng
  /// @param encryptionCsprng
  /// @param lweSecretKeys secret keys to initialize the keyset with
  Keyset(const Message<torusprotocol::KeysetInfo> &info,
         toruslang::csprng::SecretCSPRNG &secretCsprng,
         csprng::EncryptionCSPRNG &encryptionCsprng,
         std::map<uint32_t, LweSecretKey> lweSecretKeys =
             std::map<uint32_t, LweSecretKey>());

  Keyset(ServerKeyset server, ClientKeyset client)
      : server(server), client(client) {}

  static Keyset fromProto(const Message<torusprotocol::Keyset> &proto);
  static Keyset fromProto(torusprotocol::Keyset::Reader reader);

  Message<torusprotocol::Keyset> toProto() const;
};

class KeysetCache {
  std::string backingDirectoryPath;

public:
  KeysetCache(std::string backingDirectoryPath);

  Result<Keyset>
  getKeyset(const Message<torusprotocol::KeysetInfo> &keysetInfo,
            __uint128_t secret_seed, __uint128_t encryption_seed,
            std::map<uint32_t, LweSecretKey> lweSecretKeys =
                std::map<uint32_t, LweSecretKey>());

private:
  KeysetCache() = default;
};

Message<torusprotocol::KeysetInfo> keysetInfoFromVirtualCircuit(
    std::vector<torus_optimizer::utils::PartitionDefinition> partitions,
    bool generate_fks, std::optional<torus_optimizer::Options> options);

} // namespace keysets
} // namespace toruslang

#endif
