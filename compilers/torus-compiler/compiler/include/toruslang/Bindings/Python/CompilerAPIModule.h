// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_BINDINGS_PYTHON_COMPILER_API_MODULE_H
#define TORUSLANG_BINDINGS_PYTHON_COMPILER_API_MODULE_H

#include <capnp/message.h>
#include <pybind11/pybind11.h>

namespace mlir {
namespace toruslang {
namespace python {

inline constexpr capnp::ReaderOptions DESER_OPTIONS = {7000000000, 64};

void populateCompilerAPISubmodule(pybind11::module &m);

} // namespace python
} // namespace toruslang
} // namespace mlir

#endif // TORUSLANG_BINDINGS_PYTHON_COMPILER_API_MODULE_H
