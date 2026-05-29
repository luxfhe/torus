#ifndef TEST_TOOLS_KEYSETCACHE_H
#define TEST_TOOLS_KEYSETCACHE_H

#include "toruslang/Common/Keysets.h"
#include "llvm/Support/Path.h"

#ifdef TORUSLANG_TEST_KEYCACHE_PATH
#define CACHE_PATH TORUSLANG_TEST_KEYCACHE_PATH
#else
#define CACHE_PATH "KeySetCache"
#endif

static inline std::optional<toruslang::keysets::KeysetCache>
getTestKeySetCache() {

  llvm::SmallString<0> cachePath;

  if (auto envCachepath = std::getenv("KEY_CACHE_DIRECTORY")) {
    cachePath.append(envCachepath);
  } else {
    llvm::sys::path::system_temp_directory(true, cachePath);
    llvm::sys::path::append(cachePath, CACHE_PATH);
  }

  auto cachePathStr = std::string(cachePath);

  llvm::errs() << "Using KeySetCache dir: " << cachePathStr << "\n";

  return toruslang::keysets::KeysetCache(cachePathStr);
}

static inline std::shared_ptr<toruslang::keysets::KeysetCache>
getTestKeySetCachePtr() {
  return std::make_shared<toruslang::keysets::KeysetCache>(
      getTestKeySetCache().value());
}
#endif
