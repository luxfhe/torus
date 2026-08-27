// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "toruslang/Runtime/time_util.h"

#if TORUSLANG_TIMING_ENABLED

namespace mlir {
namespace toruslang {
namespace time_util {

bool timing_enabled = false;
struct timespec timestamp;

} // namespace time_util
} // namespace toruslang
} // namespace mlir

#endif
