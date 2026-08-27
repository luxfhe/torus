// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_ANALYSIS_UTILS_H
#define TORUSLANG_ANALYSIS_UTILS_H

#include <boost/outcome.h>
#include <toruslang/Common/Error.h>
#include <limits>
#include <mlir/Dialect/SCF/IR/SCF.h>
#include <mlir/IR/Location.h>

namespace mlir {
namespace toruslang {
class TripCountTracker {
public:
  void pushTripCount(mlir::Operation *op, std::optional<int64_t> n) {
    if (tripCount.has_value()) {
      if (n.has_value()) {
        assert(std::numeric_limits<int64_t>::max() / n.value() >
               tripCount.value());

        tripCount = tripCount.value() * n.value();
      } else {
        savedTripCount = *tripCount;
        tripCount = std::nullopt;
        firstDynamicTripCountOp = op;
      }
    }
  }

  void popTripCount(mlir::Operation *op, std::optional<int64_t> n) {
    if (n.has_value()) {
      if (tripCount.has_value()) {
        tripCount = tripCount.value() / n.value();
      }
    } else {
      if (firstDynamicTripCountOp == op) {
        tripCount = savedTripCount;
      }
      firstDynamicTripCountOp = nullptr;
    }
  }

  std::optional<int64_t> getTripCount() { return tripCount; }

protected:
  std::optional<int64_t> tripCount = 1;
  size_t savedTripCount;
  mlir::Operation *firstDynamicTripCountOp = nullptr;
};

/// Get the string representation of a location
std::string locationString(mlir::Location loc);

} // namespace toruslang
} // namespace mlir

#endif
