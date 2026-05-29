#include <toruslang/Analysis/Utils.h>
#include <mlir/Dialect/Arith/IR/Arith.h>

using ::toruslang::error::StringError;

namespace mlir {
namespace toruslang {
std::string locationString(mlir::Location loc) {
  auto location = std::string();
  auto locationStream = llvm::raw_string_ostream(location);
  loc->print(locationStream);
  return location;
}
} // namespace toruslang
} // namespace mlir
