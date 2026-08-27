// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_SUPPORT_UTILS_H_
#define TORUSLANG_SUPPORT_UTILS_H_

#include "torus-protocol.capnp.h"
#include "toruslang/Runtime/context.h"
#include "toruslang/Support/Error.h"
#include "llvm/ADT/SmallVector.h"

namespace toruslang {

/// prefix function name with `torus_` to avoid collision with other function
std::string prefixFuncName(llvm::StringRef funcName);

// construct the function name of the wrapper function that unify function calls
// of compiled circuit
std::string makePackedFunctionName(llvm::StringRef name);

// memref is a struct which is flattened aligned, allocated pointers, offset,
// and two array of rank size for sizes and strides.
uint64_t numArgOfRankedMemrefCallingConvention(uint64_t rank);

template <typename V, unsigned int N>
llvm::raw_ostream &operator<<(llvm::raw_ostream &OS,
                              const llvm::SmallVector<V, N> vect) {
  OS << "[";
  for (auto v : vect) {
    OS << v << ",";
  }
  OS << "]";
  return OS;
}
} // namespace toruslang

#endif
