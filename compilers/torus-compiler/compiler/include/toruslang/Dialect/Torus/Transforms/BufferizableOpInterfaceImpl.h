// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_TORUS_BUFFERIZABLEOPINTERFACEIMPL_H
#define TORUSLANG_DIALECT_TORUS_BUFFERIZABLEOPINTERFACEIMPL_H

namespace mlir {
class DialectRegistry;

namespace toruslang {
namespace Torus {
void registerBufferizableOpInterfaceExternalModels(DialectRegistry &registry);
} // namespace Torus
} // namespace toruslang
} // namespace mlir

#endif
