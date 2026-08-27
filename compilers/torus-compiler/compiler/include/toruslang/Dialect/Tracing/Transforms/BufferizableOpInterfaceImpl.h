// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_TRACING_BUFFERIZABLEOPINTERFACEIMPL_H
#define TORUSLANG_DIALECT_TRACING_BUFFERIZABLEOPINTERFACEIMPL_H

namespace mlir {
class DialectRegistry;

namespace toruslang {
namespace Tracing {
void registerBufferizableOpInterfaceExternalModels(DialectRegistry &registry);
} // namespace Tracing
} // namespace toruslang
} // namespace mlir

#endif
