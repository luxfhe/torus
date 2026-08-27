// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_RT_BUFFERIZABLEOPINTERFACEIMPL_H
#define TORUSLANG_DIALECT_RT_BUFFERIZABLEOPINTERFACEIMPL_H

namespace mlir {
class DialectRegistry;

namespace toruslang {
namespace RT {
void registerBufferizableOpInterfaceExternalModels(DialectRegistry &registry);
} // namespace RT
} // namespace toruslang
} // namespace mlir

#endif
