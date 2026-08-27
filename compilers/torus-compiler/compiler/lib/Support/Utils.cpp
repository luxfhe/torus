// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include <toruslang/Support/Utils.h>

namespace toruslang {

std::string prefixFuncName(llvm::StringRef funcName) {
  return "torus_" + funcName.str();
}

std::string makePackedFunctionName(llvm::StringRef name) {
  return "_mlir_" + name.str();
}

uint64_t numArgOfRankedMemrefCallingConvention(uint64_t rank) {
  return 3 + 2 * rank;
}

} // namespace toruslang
