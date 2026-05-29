// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_CONVERSION_UTILS_H_
#define TORUSLANG_CONVERSION_UTILS_H_

#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Transforms/DialectConversion.h"

namespace mlir {
namespace toruslang {

mlir::Type getDynamicMemrefWithUnknownOffset(mlir::RewriterBase &rewriter,
                                             size_t rank);

// Returns `memref.cast %0 : memref<...xAxT> to memref<...x?xT>`
mlir::Value getCastedMemRef(mlir::RewriterBase &rewriter, mlir::Value value);

mlir::Value globalMemrefFromArrayAttr(mlir::RewriterBase &rewriter,
                                      mlir::Location loc,
                                      mlir::ArrayAttr arrAttr);

mlir::Operation *convertOpWithBlocks(mlir::Operation *op,
                                     mlir::ValueRange newOperands,
                                     mlir::TypeRange newResultTypes,
                                     mlir::TypeConverter &typeConverter,
                                     mlir::ConversionPatternRewriter &rewriter);

} // namespace toruslang
} // namespace mlir
#endif
