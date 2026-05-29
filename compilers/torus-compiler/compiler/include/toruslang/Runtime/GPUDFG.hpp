// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_GPUDFG_HPP
#define TORUSLANG_GPUDFG_HPP

#ifdef TORUSLANG_CUDA_SUPPORT
#include "device.h"
#include "keyswitch.h"
#include "linear_algebra.h"
#include "programmable_bootstrap.h"

#endif

namespace mlir {
namespace toruslang {
namespace gpu_dfg {

bool check_cuda_device_available();
bool check_cuda_runtime_enabled();

} // namespace gpu_dfg
} // namespace toruslang
} // namespace mlir

#endif
