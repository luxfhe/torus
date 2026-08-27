// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_CONVERSION_GLOBALFHECONTEXT_H_
#define TORUSLANG_CONVERSION_GLOBALFHECONTEXT_H_
#include <cstddef>
#include <cstdint>
#include <vector>

#include "toruslang/Support/V0Parameters.h"
#include "llvm/ADT/Optional.h"

namespace mlir {
namespace toruslang {

struct V0FHEContext {
  V0FHEContext() = delete;
  V0FHEContext(const V0FHEConstraint &constraint,
               const optimizer::Solution solution)
      : constraint(constraint), solution(solution) {}

  V0FHEConstraint constraint;
  optimizer::Solution solution;
};
} // namespace toruslang
} // namespace mlir

#endif
