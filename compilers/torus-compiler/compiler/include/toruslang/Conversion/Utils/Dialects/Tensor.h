// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_CONVERSION_UTILS_DIALECTS_TENSOR_H_
#define TORUSLANG_CONVERSION_UTILS_DIALECTS_TENSOR_H_

#include "toruslang/Conversion/Utils/ReinstantiatingOpTypeConversion.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"

namespace mlir {
namespace toruslang {

//
// Specializations for CollapseShapeOp
//

// Specialization copying attributes not necessary, as the base
// template works correctly
template <>
mlir::LogicalResult
TypeConvertingReinstantiationPattern<tensor::CollapseShapeOp, false>::
    matchAndRewrite(
        tensor::CollapseShapeOp oldOp,
        mlir::OpConversionPattern<tensor::CollapseShapeOp>::OpAdaptor adaptor,
        mlir::ConversionPatternRewriter &rewriter) const;
//
// Specializations for FromElementsOp
//
template <>
mlir::LogicalResult
TypeConvertingReinstantiationPattern<mlir::tensor::FromElementsOp, false>::
    matchAndRewrite(
        tensor::FromElementsOp oldOp,
        mlir::OpConversionPattern<mlir::tensor::FromElementsOp>::OpAdaptor
            adaptor,
        mlir::ConversionPatternRewriter &rewriter) const;

//
// Specializations for ExpandShapeOp
//

// Specialization copying attributes not necessary, as the base
// template works correctly

template <>
mlir::LogicalResult
TypeConvertingReinstantiationPattern<tensor::ExpandShapeOp, false>::
    matchAndRewrite(
        tensor::ExpandShapeOp oldOp,
        mlir::OpConversionPattern<tensor::ExpandShapeOp>::OpAdaptor adaptor,
        mlir::ConversionPatternRewriter &rewriter) const;

//
// Specializations for GenerateOp
//

// Specialization NOT copying attributes omitted
template <>
mlir::LogicalResult
TypeConvertingReinstantiationPattern<tensor::GenerateOp, true>::matchAndRewrite(
    tensor::GenerateOp oldOp,
    mlir::OpConversionPattern<tensor::GenerateOp>::OpAdaptor adaptor,
    mlir::ConversionPatternRewriter &rewriter) const;

} // namespace toruslang
} // namespace mlir

#endif // TORUSLANG_CONVERSION_UTILS_DIALECTS_TENSOR_H_
