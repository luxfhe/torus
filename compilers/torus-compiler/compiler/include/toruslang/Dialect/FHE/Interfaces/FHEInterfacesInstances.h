// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_TORUS_FHEINTERFACESINSTANCES_H
#define TORUSLANG_DIALECT_TORUS_FHEINTERFACESINSTANCES_H

#include "toruslang/Dialect/FHE/Interfaces/FHEInterfaces.h"

namespace mlir {
class DialectRegistry;

namespace toruslang {
namespace FHE {
void registerFheInterfacesExternalModels(DialectRegistry &registry);
} // namespace FHE
} // namespace toruslang
} // namespace mlir

#endif
