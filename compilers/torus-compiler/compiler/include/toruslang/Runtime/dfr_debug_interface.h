// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DRF_DEBUG_INTERFACE_H
#define TORUSLANG_DRF_DEBUG_INTERFACE_H

#include <stdint.h>
#include <unistd.h>

extern "C" {
size_t _dfr_debug_get_node_id();
size_t _dfr_debug_get_worker_id();
void _dfr_debug_print_task(const char *name, size_t inputs, size_t outputs);
void _dfr_print_debug(size_t val);
}
#endif
