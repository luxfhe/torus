// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_CONVERSION_RTOPCONVERTER_H_
#define TORUSLANG_CONVERSION_RTOPCONVERTER_H_

#include "toruslang/Conversion/Utils/Legality.h"
#include "toruslang/Conversion/Utils/ReinstantiatingOpTypeConversion.h"
#include "toruslang/Dialect/RT/IR/RTOps.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Transforms/DialectConversion.h"

namespace mlir {
namespace toruslang {

inline void
populateWithRTTypeConverterPatterns(mlir::RewritePatternSet &patterns,
                                    mlir::ConversionTarget &target,
                                    mlir::TypeConverter &converter) {
  patterns.add<
      mlir::toruslang::TypeConvertingReinstantiationPattern<
          mlir::toruslang::RT::DataflowTaskOp>,
      mlir::toruslang::TypeConvertingReinstantiationPattern<
          mlir::toruslang::RT::DataflowYieldOp>,
      mlir::toruslang::TypeConvertingReinstantiationPattern<
          mlir::toruslang::RT::MakeReadyFutureOp>,
      mlir::toruslang::TypeConvertingReinstantiationPattern<
          mlir::toruslang::RT::AwaitFutureOp>,
      mlir::toruslang::TypeConvertingReinstantiationPattern<
          mlir::toruslang::RT::CreateAsyncTaskOp, true>,
      mlir::toruslang::TypeConvertingReinstantiationPattern<
          mlir::toruslang::RT::BuildReturnPtrPlaceholderOp>,
      mlir::toruslang::TypeConvertingReinstantiationPattern<
          mlir::toruslang::RT::DerefWorkFunctionArgumentPtrPlaceholderOp>,
      mlir::toruslang::TypeConvertingReinstantiationPattern<
          mlir::toruslang::RT::DerefReturnPtrPlaceholderOp>,
      mlir::toruslang::TypeConvertingReinstantiationPattern<
          mlir::toruslang::RT::WorkFunctionReturnOp>,
      mlir::toruslang::TypeConvertingReinstantiationPattern<
          mlir::toruslang::RT::RegisterTaskWorkFunctionOp>>(
      patterns.getContext(), converter);

  mlir::toruslang::addDynamicallyLegalTypeOp<
      mlir::toruslang::RT::DataflowTaskOp>(target, converter);
  mlir::toruslang::addDynamicallyLegalTypeOp<
      mlir::toruslang::RT::DataflowYieldOp>(target, converter);
  mlir::toruslang::addDynamicallyLegalTypeOp<
      mlir::toruslang::RT::MakeReadyFutureOp>(target, converter);
  mlir::toruslang::addDynamicallyLegalTypeOp<
      mlir::toruslang::RT::AwaitFutureOp>(target, converter);
  mlir::toruslang::addDynamicallyLegalTypeOp<
      mlir::toruslang::RT::CreateAsyncTaskOp>(target, converter);
  mlir::toruslang::addDynamicallyLegalTypeOp<
      mlir::toruslang::RT::BuildReturnPtrPlaceholderOp>(target, converter);
  mlir::toruslang::addDynamicallyLegalTypeOp<
      mlir::toruslang::RT::DerefWorkFunctionArgumentPtrPlaceholderOp>(
      target, converter);
  mlir::toruslang::addDynamicallyLegalTypeOp<
      mlir::toruslang::RT::DerefReturnPtrPlaceholderOp>(target, converter);
  mlir::toruslang::addDynamicallyLegalTypeOp<
      mlir::toruslang::RT::WorkFunctionReturnOp>(target, converter);
  mlir::toruslang::addDynamicallyLegalTypeOp<
      mlir::toruslang::RT::RegisterTaskWorkFunctionOp>(target, converter);
}
} // namespace toruslang
} // namespace mlir

#endif
