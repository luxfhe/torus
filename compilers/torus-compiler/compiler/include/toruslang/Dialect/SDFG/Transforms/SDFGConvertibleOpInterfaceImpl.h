// Part of the Concrete Compiler Project, under the BSD3 License with Zama
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_SDFG_SDFGCONVERTIBLEOPINTERFACEIMPL_H
#define TORUSLANG_DIALECT_SDFG_SDFGCONVERTIBLEOPINTERFACEIMPL_H

namespace mlir {
class DialectRegistry;

namespace toruslang {
namespace SDFG {
void registerSDFGConvertibleOpInterfaceExternalModels(
    DialectRegistry &registry);
} // namespace SDFG
} // namespace toruslang
} // namespace mlir

#endif
