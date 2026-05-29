// Part of the Concrete Compiler Project, under the BSD3 License with Zama
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_CONVERSION_UTILS_LEGALITY_H_
#define TORUSLANG_CONVERSION_UTILS_LEGALITY_H_

#include <mlir/Transforms/DialectConversion.h>

namespace mlir {
namespace toruslang {

template <typename Op>
void addDynamicallyLegalTypeOp(mlir::ConversionTarget &target,
                               mlir::TypeConverter &typeConverter) {
  target.addDynamicallyLegalOp<Op>([&](Op op) {
    return typeConverter.isLegal(op->getOperandTypes()) &&
           typeConverter.isLegal(op->getResultTypes());
  });
}

} // namespace toruslang
} // namespace mlir

#endif
