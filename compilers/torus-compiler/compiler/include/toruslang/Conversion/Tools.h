// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "mlir/IR/PatternMatch.h"

mlir::LogicalResult insertForwardDeclaration(mlir::Operation *op,
                                             mlir::OpBuilder &rewriter,
                                             llvm::StringRef funcName,
                                             mlir::FunctionType funcType);

/// \brief Returns the value of the context argument from the enclosing func
///
/// \param op initial operation to start the search from
/// \return mlir::Value the context value
mlir::Value getContextArgument(mlir::Operation *op);
