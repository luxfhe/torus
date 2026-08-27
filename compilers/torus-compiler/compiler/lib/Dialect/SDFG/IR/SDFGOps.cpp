// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "mlir/IR/Builders.h"

#include "toruslang/Dialect/SDFG/IR/SDFGOps.h"
#include "toruslang/Dialect/SDFG/IR/SDFGTypes.h"

#include "toruslang/Dialect/SDFG/IR/SDFGEnums.cpp.inc"
#include <mlir/Support/LogicalResult.h>

#define GET_OP_CLASSES
#include "toruslang/Dialect/SDFG/IR/SDFGOps.cpp.inc"

namespace mlir {
namespace toruslang {
namespace SDFG {
mlir::LogicalResult Put::verify() {
  mlir::Type streamElementType =
      getStream().getType().cast<StreamType>().getElementType();
  mlir::Type elementType = getData().getType();

  if (streamElementType != elementType) {
    emitError()
        << "The type " << elementType
        << " of the element to be written does not match the element type "
        << streamElementType << " of the stream.";
    return mlir::failure();
  }

  return mlir::success();
}

mlir::LogicalResult MakeProcess::checkStreams(size_t numIn, size_t numOut) {
  mlir::OperandRange streams = this->getStreams();

  if (streams.size() != numIn + numOut) {
    emitError() << "Process `" << stringifyProcessKind(getType())
                << "` expects 3 streams, but " << streams.size()
                << " were given.";
    return mlir::failure();
  }

  for (size_t i = 0; i < numIn; i++) {
    MakeStream in = dyn_cast_or_null<MakeStream>(streams[i].getDefiningOp());

    if (in && !in.createsInputStream()) {
      emitError() << "Stream #" << (i + 1) << " of process `"
                  << stringifyProcessKind(getType())
                  << "` must be an input stream.";
      return mlir::failure();
    }
  }

  for (size_t i = numIn; i < numIn + numOut; i++) {
    MakeStream out = dyn_cast_or_null<MakeStream>(streams[i].getDefiningOp());

    if (out && !out.createsOutputStream()) {
      emitError() << "Stream #" << (i + 1) << " of process `"
                  << stringifyProcessKind(getType())
                  << "` must be an output stream.";
      return mlir::failure();
    }
  }

  return mlir::success();
}

mlir::LogicalResult MakeProcess::verify() {
  switch (getType()) {
  case ProcessKind::add_eint:
    return checkStreams(2, 1);
  case ProcessKind::add_eint_int:
    return checkStreams(2, 1);
  case ProcessKind::mul_eint_int:
    return checkStreams(2, 1);
  case ProcessKind::neg_eint:
    return checkStreams(1, 1);
  case ProcessKind::keyswitch:
    return checkStreams(1, 1);
  case ProcessKind::bootstrap:
    return checkStreams(2, 1);
  case ProcessKind::batched_add_eint:
    return checkStreams(2, 1);
  case ProcessKind::batched_add_eint_int:
    return checkStreams(2, 1);
  case ProcessKind::batched_add_eint_int_cst:
    return checkStreams(2, 1);
  case ProcessKind::batched_mul_eint_int:
    return checkStreams(2, 1);
  case ProcessKind::batched_mul_eint_int_cst:
    return checkStreams(2, 1);
  case ProcessKind::batched_neg_eint:
    return checkStreams(1, 1);
  case ProcessKind::batched_keyswitch:
    return checkStreams(1, 1);
  case ProcessKind::batched_bootstrap:
    return checkStreams(2, 1);
  case ProcessKind::batched_mapped_bootstrap:
    return checkStreams(2, 1);
  }

  return mlir::failure();
}
} // namespace SDFG
} // namespace toruslang
} // namespace mlir
