
// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "toruslang/Common/Keys.h"
#include "capnp/any.h"
#include "torus-cpu.h"
#include "torus-protocol.capnp.h"
#include "toruslang/Common/Csprng.h"
#include "toruslang/Common/Protocol.h"
#include <climits>
#include <cstdint>
#include <memory>
#include <stdlib.h>

using toruslang::csprng::EncryptionCSPRNG;
using toruslang::csprng::SecretCSPRNG;
using toruslang::protocol::Message;
using toruslang::protocol::protoPayloadToSharedVector;
using toruslang::protocol::vectorToProtoPayload;

namespace toruslang {
namespace keys {

template <typename ProtoKey, typename ProtoKeyInfo, typename Key>
Message<ProtoKey> keyToProto(const Key &key) {
  Message<ProtoKey> output;
  auto proto = output.asBuilder();
  proto.setInfo(key.getInfo().asReader());
  proto.setPayload(vectorToProtoPayload(key.getTransportBuffer()).asReader());
  return std::move(output);
}

void writeSeed(struct Uint128 seed, std::vector<uint64_t> &buffer) {
  csprng::writeSeed(seed, buffer.data());
}

void readSeed(struct Uint128 &seed, std::vector<uint64_t> &buffer) {
  csprng::readSeed(seed, buffer.data());
}

LweSecretKey::LweSecretKey(Message<torusprotocol::LweSecretKeyInfo> info,
                           SecretCSPRNG &csprng) {
  // Allocate the buffer
  buffer = std::make_shared<std::vector<uint64_t>>(
      info.asReader().getParams().getLweDimension());

  // We copy the information.
  this->info = info;

#ifdef TORUSLANG_GENERATE_UNSECURE_SECRET_KEYS
  // In insecure debug mode, the secret key is filled with zeros.
  getApproval();
  std::fill(buffer->begin(), buffer->end(), 0);
#else
  // Initialize the lwe secret key buffer
  torus_cpu_init_secret_key_u64(
      buffer->data(), info.asReader().getParams().getLweDimension(),
      csprng.ptr);
#endif
}

LweSecretKey
LweSecretKey::fromProto(const Message<torusprotocol::LweSecretKey> &proto) {
  return fromProto(proto.asReader());
}

LweSecretKey
LweSecretKey::fromProto(torusprotocol::LweSecretKey::Reader reader) {

  auto info = Message<torusprotocol::LweSecretKeyInfo>(reader.getInfo());
  auto vector = protoPayloadToSharedVector<uint64_t>(reader.getPayload());
  return LweSecretKey(vector, info);
}

Message<torusprotocol::LweSecretKey> LweSecretKey::toProto() const {
  return keyToProto<torusprotocol::LweSecretKey,
                    torusprotocol::LweSecretKeyInfo, LweSecretKey>(*this);
}

const uint64_t *LweSecretKey::getRawPtr() const { return this->buffer->data(); }

size_t LweSecretKey::getSize() const { return this->buffer->size(); }

const Message<torusprotocol::LweSecretKeyInfo> &
LweSecretKey::getInfo() const {
  return this->info;
}

const std::vector<uint64_t> &LweSecretKey::getBuffer() const {
  return *this->buffer;
}

LweBootstrapKey::LweBootstrapKey(
    Message<torusprotocol::LweBootstrapKeyInfo> info,
    const LweSecretKey &inputKey, const LweSecretKey &outputKey,
    EncryptionCSPRNG &csprng)
    : LweBootstrapKey(info) {
  assert(inputKey.info.asReader().getParams().getLweDimension() ==
         info.asReader().getParams().getInputLweDimension());
  assert(outputKey.info.asReader().getParams().getLweDimension() ==
         info.asReader().getParams().getGlweDimension() *
             info.asReader().getParams().getPolynomialSize());

  auto params = info.asReader().getParams();
  auto compression = info.asReader().getCompression();

  switch (compression) {
  case torusprotocol::Compression::NONE:
    buffer->resize(torus_cpu_bootstrap_key_size_u64(
        params.getLevelCount(), params.getGlweDimension(),
        params.getPolynomialSize(), params.getInputLweDimension()));
    torus_cpu_init_lwe_bootstrap_key_u64(
        buffer->data(), inputKey.buffer->data(), outputKey.buffer->data(),
        params.getInputLweDimension(), params.getPolynomialSize(),
        params.getGlweDimension(), params.getLevelCount(), params.getBaseLog(),
        params.getVariance(), Parallelism::Rayon, csprng.ptr);
    break;
  case torusprotocol::Compression::SEED:
    seededBuffer->resize(torus_cpu_seeded_bootstrap_key_size_u64(
                             params.getLevelCount(), params.getGlweDimension(),
                             params.getPolynomialSize(),
                             params.getInputLweDimension()) +
                         2 /* For the seed*/);
    struct Uint128 seed;
    csprng::getRandomSeed(&seed);
    writeSeed(seed, *seededBuffer);
    torus_cpu_init_seeded_lwe_bootstrap_key_u64(
        seededBuffer->data() + 2, inputKey.buffer->data(),
        outputKey.buffer->data(), params.getInputLweDimension(),
        params.getPolynomialSize(), params.getGlweDimension(),
        params.getLevelCount(), params.getBaseLog(), seed, params.getVariance(),
        Parallelism::Rayon);
    break;
  default:
    assert(false && "Unsupported compression type for bootstrap key");
  }
};

LweBootstrapKey LweBootstrapKey::fromProto(
    const Message<torusprotocol::LweBootstrapKey> &key) {
  return fromProto(key.asReader());
}

LweBootstrapKey
LweBootstrapKey::fromProto(torusprotocol::LweBootstrapKey::Reader reader) {
  auto info = Message<torusprotocol::LweBootstrapKeyInfo>(reader.getInfo());
  auto vector = protoPayloadToSharedVector<uint64_t>(reader.getPayload());
  LweBootstrapKey key(info);
  switch (info.asReader().getCompression()) {
  case torusprotocol::Compression::NONE:
    key.buffer = vector;
    break;
  case torusprotocol::Compression::SEED:
    key.seededBuffer = vector;
    break;
  default:
    assert(false && "Unsupported compression type for bootstrap key");
  }
  return key;
}

Message<torusprotocol::LweBootstrapKey> LweBootstrapKey::toProto() const {
  return keyToProto<torusprotocol::LweBootstrapKey,
                    torusprotocol::LweBootstrapKeyInfo, LweBootstrapKey>(
      *this);
}

const std::vector<uint64_t> &LweBootstrapKey::getBuffer() {
  decompress();
  return *buffer;
}

const std::vector<uint64_t> &LweBootstrapKey::getTransportBuffer() const {
  switch (info.asReader().getCompression()) {
  case torusprotocol::Compression::NONE:
    return *buffer;
  case torusprotocol::Compression::SEED:
    assert(!seededBuffer->empty());
    return *seededBuffer;
  default:
    assert(false && "Unsupported compression type for bootstrap key");
  }
}

const Message<torusprotocol::LweBootstrapKeyInfo> &
LweBootstrapKey::getInfo() const {
  return this->info;
}

void LweBootstrapKey::decompress() {
  switch (info.asReader().getCompression()) {
  case torusprotocol::Compression::NONE:
    return;
  case torusprotocol::Compression::SEED: {
    if (*decompressed)
      return;
    const std::lock_guard<std::mutex> guard(*decompress_mutext);
    if (*decompressed)
      return;
    auto params = info.asReader().getParams();
    buffer->resize(torus_cpu_bootstrap_key_size_u64(
        params.getLevelCount(), params.getGlweDimension(),
        params.getPolynomialSize(), params.getInputLweDimension()));
    struct Uint128 seed;
    readSeed(seed, *seededBuffer);
    torus_cpu_decompress_seeded_lwe_bootstrap_key_u64(
        buffer->data(), seededBuffer->data() + 2, params.getInputLweDimension(),
        params.getPolynomialSize(), params.getGlweDimension(),
        params.getLevelCount(), params.getBaseLog(), seed, Parallelism::Rayon);
    *decompressed = true;
    return;
  }
  default:
    assert(false && "Unsupported compression type for bootstrap key");
  }
}

LweKeyswitchKey::LweKeyswitchKey(
    Message<torusprotocol::LweKeyswitchKeyInfo> info,
    const LweSecretKey &inputKey, const LweSecretKey &outputKey,
    EncryptionCSPRNG &csprng)
    : LweKeyswitchKey(info) {
  assert(inputKey.info.asReader().getParams().getLweDimension() ==
         info.asReader().getParams().getInputLweDimension());
  assert(outputKey.info.asReader().getParams().getLweDimension() ==
         info.asReader().getParams().getOutputLweDimension());

  auto params = info.asReader().getParams();
  auto compression = info.asReader().getCompression();

  switch (compression) {
  case torusprotocol::Compression::NONE:
    buffer->resize(torus_cpu_keyswitch_key_size_u64(
        params.getLevelCount(), params.getInputLweDimension(),
        params.getOutputLweDimension()));
    torus_cpu_init_lwe_keyswitch_key_u64(
        buffer->data(), inputKey.buffer->data(), outputKey.buffer->data(),
        params.getInputLweDimension(), params.getOutputLweDimension(),
        params.getLevelCount(), params.getBaseLog(), params.getVariance(),
        csprng.ptr);
    return;
  case torusprotocol::Compression::SEED:
    seededBuffer->resize(
        torus_cpu_seeded_keyswitch_key_size_u64(
            params.getLevelCount(), params.getInputLweDimension()) +
        2 /* for seed*/);
    struct Uint128 seed;
    csprng::getRandomSeed(&seed);
    writeSeed(seed, *seededBuffer);
    torus_cpu_init_seeded_lwe_keyswitch_key_u64(
        seededBuffer->data() + 2, inputKey.buffer->data(),
        outputKey.buffer->data(), params.getInputLweDimension(),
        params.getOutputLweDimension(), params.getLevelCount(),
        params.getBaseLog(), seed, params.getVariance());
    return;
  default:
    assert(false && "Unsupported compression type for keyswitch key");
    break;
  }
}

LweKeyswitchKey LweKeyswitchKey::fromProto(
    const Message<torusprotocol::LweKeyswitchKey> &proto) {
  return fromProto(proto.asReader());
}

LweKeyswitchKey
LweKeyswitchKey::fromProto(torusprotocol::LweKeyswitchKey::Reader reader) {
  auto info = Message<torusprotocol::LweKeyswitchKeyInfo>(reader.getInfo());
  auto vector = protoPayloadToSharedVector<uint64_t>(reader.getPayload());
  LweKeyswitchKey key(info);
  switch (info.asReader().getCompression()) {
  case torusprotocol::Compression::NONE:
    key.buffer = vector;
    break;
  case torusprotocol::Compression::SEED:
    key.seededBuffer = vector;
    break;
  default:
    assert(false && "Unsupported compression type for bootstrap key");
  }
  return key;
}

Message<torusprotocol::LweKeyswitchKey> LweKeyswitchKey::toProto() const {
  return keyToProto<torusprotocol::LweKeyswitchKey,
                    torusprotocol::LweKeyswitchKeyInfo, LweKeyswitchKey>(
      *this);
}

const Message<torusprotocol::LweKeyswitchKeyInfo> &
LweKeyswitchKey::getInfo() const {
  return this->info;
}

const std::vector<uint64_t> &LweKeyswitchKey::getBuffer() {
  decompress();
  return *buffer;
}

const std::vector<uint64_t> &LweKeyswitchKey::getTransportBuffer() const {
  switch (info.asReader().getCompression()) {
  case torusprotocol::Compression::NONE:
    return *buffer;
  case torusprotocol::Compression::SEED:
    assert(!seededBuffer->empty());
    return *seededBuffer;
  default:
    assert(false && "Unsupported compression type for bootstrap key");
  }
}

void LweKeyswitchKey::decompress() {
  switch (info.asReader().getCompression()) {
  case torusprotocol::Compression::NONE:
    return;
  case torusprotocol::Compression::SEED: {
    if (*decompressed)
      return;
    const std::lock_guard<std::mutex> guard(*decompress_mutext);
    if (*decompressed)
      return;
    auto params = info.asReader().getParams();
    buffer->resize(torus_cpu_keyswitch_key_size_u64(
        params.getLevelCount(), params.getInputLweDimension(),
        params.getOutputLweDimension()));
    struct Uint128 seed;
    readSeed(seed, *seededBuffer);
    torus_cpu_decompress_seeded_lwe_keyswitch_key_u64(
        buffer->data(), seededBuffer->data() + 2, params.getInputLweDimension(),
        params.getOutputLweDimension(), params.getLevelCount(),
        params.getBaseLog(), seed, Parallelism::Rayon);
    *decompressed = true;
    return;
  }
  default:
    assert(false && "Unsupported compression type for bootstrap key");
  }
}

PackingKeyswitchKey::PackingKeyswitchKey(
    Message<torusprotocol::PackingKeyswitchKeyInfo> info,
    const LweSecretKey &inputKey, const LweSecretKey &outputKey,
    EncryptionCSPRNG &csprng) {
  assert(info.asReader().getParams().getGlweDimension() *
             info.asReader().getParams().getPolynomialSize() ==
         outputKey.info.asReader().getParams().getLweDimension());

  // Allocate the buffer
  auto params = info.asReader().getParams();
  auto bufferSize = torus_cpu_lwe_packing_keyswitch_key_size(
                        params.getGlweDimension(), params.getPolynomialSize(),
                        params.getLevelCount(), params.getInputLweDimension()) *
                    (params.getGlweDimension() + 1);
  buffer = std::make_shared<std::vector<uint64_t>>();
  (*buffer).resize(bufferSize);

  // We copy the information.
  this->info = info;

  // Initialize the keyswitch key buffer
  torus_cpu_init_lwe_circuit_bootstrap_private_functional_packing_keyswitch_keys_u64(
      buffer->data(), inputKey.buffer->data(), outputKey.buffer->data(),
      params.getInputLweDimension(), params.getPolynomialSize(),
      params.getGlweDimension(), params.getLevelCount(), params.getBaseLog(),
      params.getVariance(), Parallelism::Rayon, csprng.ptr);
}

PackingKeyswitchKey PackingKeyswitchKey::fromProto(
    const Message<torusprotocol::PackingKeyswitchKey> &proto) {
  return fromProto(proto.asReader());
}

PackingKeyswitchKey PackingKeyswitchKey::fromProto(
    torusprotocol::PackingKeyswitchKey::Reader reader) {
  auto info =
      Message<torusprotocol::PackingKeyswitchKeyInfo>(reader.getInfo());
  auto vector = protoPayloadToSharedVector<uint64_t>(reader.getPayload());
  return PackingKeyswitchKey(vector, info);
}

Message<torusprotocol::PackingKeyswitchKey>
PackingKeyswitchKey::toProto() const {
  return keyToProto<torusprotocol::PackingKeyswitchKey,
                    torusprotocol::PackingKeyswitchKeyInfo,
                    PackingKeyswitchKey>(*this);
}

const uint64_t *PackingKeyswitchKey::getRawPtr() const {
  return this->buffer->data();
}

size_t PackingKeyswitchKey::getSize() const { return this->buffer->size(); }

const Message<torusprotocol::PackingKeyswitchKeyInfo> &
PackingKeyswitchKey::getInfo() const {
  return this->info;
}

const std::vector<uint64_t> &PackingKeyswitchKey::getBuffer() const {
  return *this->buffer;
}

} // namespace keys
} // namespace toruslang
