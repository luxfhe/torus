// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_CONCRETE_BUFFERIZABLEOPINTERFACEIMPL_H
#define TORUSLANG_DIALECT_CONCRETE_BUFFERIZABLEOPINTERFACEIMPL_H

namespace mlir {
class DialectRegistry;

namespace toruslang {
namespace Concrete {
void registerBufferizableOpInterfaceExternalModels(DialectRegistry &registry);
} // namespace Concrete
} // namespace toruslang
} // namespace mlir

#endif
