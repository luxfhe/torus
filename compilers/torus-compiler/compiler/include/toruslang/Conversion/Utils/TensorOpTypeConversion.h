// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_CONVERSION_TENSOROPTYPECONVERSIONPATTERN_H_
#define TORUSLANG_CONVERSION_TENSOROPTYPECONVERSIONPATTERN_H_

#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Transforms/DialectConversion.h"

#include "toruslang/Conversion/Utils/Dialects/Tensor.h"
#include "toruslang/Conversion/Utils/Legality.h"

namespace mlir {
namespace toruslang {

inline void
populateWithTensorTypeConverterPatterns(mlir::RewritePatternSet &patterns,
                                        mlir::ConversionTarget &target,
                                        mlir::TypeConverter &typeConverter) {
  // ExtractOp
  patterns.add<TypeConvertingReinstantiationPattern<mlir::tensor::ExtractOp>>(
      patterns.getContext(), typeConverter);
  addDynamicallyLegalTypeOp<mlir::tensor::ExtractOp>(target, typeConverter);

  // ExtractSliceOp
  patterns.add<
      TypeConvertingReinstantiationPattern<mlir::tensor::ExtractSliceOp, true>>(
      patterns.getContext(), typeConverter);
  addDynamicallyLegalTypeOp<mlir::tensor::ExtractSliceOp>(target,
                                                          typeConverter);

  // InsertOp
  patterns.add<TypeConvertingReinstantiationPattern<mlir::tensor::InsertOp>>(
      patterns.getContext(), typeConverter);
  addDynamicallyLegalTypeOp<mlir::tensor::InsertOp>(target, typeConverter);
  // InsertSliceOp
  patterns.add<
      TypeConvertingReinstantiationPattern<mlir::tensor::InsertSliceOp, true>>(
      patterns.getContext(), typeConverter);
  addDynamicallyLegalTypeOp<mlir::tensor::InsertSliceOp>(target, typeConverter);

  // FromElementsOp
  patterns
      .add<TypeConvertingReinstantiationPattern<mlir::tensor::FromElementsOp>>(
          patterns.getContext(), typeConverter);
  addDynamicallyLegalTypeOp<mlir::tensor::FromElementsOp>(target,
                                                          typeConverter);
  // TensorCollapseShapeOp
  patterns
      .add<TypeConvertingReinstantiationPattern<mlir::tensor::CollapseShapeOp>>(
          patterns.getContext(), typeConverter);
  addDynamicallyLegalTypeOp<mlir::tensor::CollapseShapeOp>(target,
                                                           typeConverter);
  // TensorExpandShapeOp
  patterns
      .add<TypeConvertingReinstantiationPattern<mlir::tensor::ExpandShapeOp>>(
          patterns.getContext(), typeConverter);
  addDynamicallyLegalTypeOp<mlir::tensor::ExpandShapeOp>(target, typeConverter);
}
} // namespace toruslang
} // namespace mlir

#endif
