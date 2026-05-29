// Part of the Concrete Compiler Project, under the BSD3 License with Zama
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_BINDINGS_PYTHON_DIALECTMODULES_H
#define TORUSLANG_BINDINGS_PYTHON_DIALECTMODULES_H

#include <pybind11/pybind11.h>

namespace mlir {
namespace toruslang {
namespace python {

void populateDialectFHESubmodule(pybind11::module &m);

} // namespace python
} // namespace toruslang
} // namespace mlir

#endif // TORUSLANG_BINDINGS_PYTHON_DIALECTMODULES_H
