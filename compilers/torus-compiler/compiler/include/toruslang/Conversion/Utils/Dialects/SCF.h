// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_CONVERSION_UTILS_DIALECTS_SCF_H_
#define TORUSLANG_CONVERSION_UTILS_DIALECTS_SCF_H_

#include "toruslang/Conversion/Utils/ReinstantiatingOpTypeConversion.h"
#include "mlir/Dialect/SCF/IR/SCF.h"

namespace mlir {
namespace toruslang {

//
// Specializations for ForOp
//

// Specialization copying attributes omitted
template <>
mlir::LogicalResult
TypeConvertingReinstantiationPattern<scf::ForOp, false>::matchAndRewrite(
    scf::ForOp oldOp, mlir::OpConversionPattern<scf::ForOp>::OpAdaptor adaptor,
    mlir::ConversionPatternRewriter &rewriter) const;

//
// Specializations for ForallOp
//
template <>
mlir::LogicalResult
TypeConvertingReinstantiationPattern<scf::ForallOp, false>::matchAndRewrite(
    scf::ForallOp oldOp,
    mlir::OpConversionPattern<scf::ForallOp>::OpAdaptor adaptor,
    mlir::ConversionPatternRewriter &rewriter) const;

//
// Specializations for InParallelOp
//
template <>
mlir::LogicalResult
TypeConvertingReinstantiationPattern<scf::InParallelOp, false>::matchAndRewrite(
    scf::InParallelOp oldOp,
    mlir::OpConversionPattern<scf::InParallelOp>::OpAdaptor adaptor,
    mlir::ConversionPatternRewriter &rewriter) const;

} // namespace toruslang
} // namespace mlir

#endif
