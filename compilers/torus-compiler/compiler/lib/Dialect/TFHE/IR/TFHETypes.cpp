// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include <toruslang/Dialect/TFHE/IR/TFHETypes.h>
#include <mlir/IR/DialectImplementation.h>

namespace mlir {
namespace toruslang {
namespace TFHE {

void printSigned(mlir::AsmPrinter &p, signed i) {
  if (i == -1)
    p << "_";
  else
    p << i;
}

void GLWECipherTextType::print(mlir::AsmPrinter &p) const {
  p << "<";
  p << getKey();
  p << ">";
}

mlir::Type GLWECipherTextType::parse(AsmParser &parser) {
  if (parser.parseLess())
    return mlir::Type();

  // First parameters block
  FailureOr<mlir::toruslang::TFHE::GLWESecretKey> maybeKey =
      FieldParser<GLWESecretKey>::parse(parser);
  if (failed(maybeKey))
    return mlir::Type();

  if (parser.parseGreater())
    return mlir::Type();

  Location loc = parser.getEncodedSourceLoc(parser.getNameLoc());

  return getChecked(loc, loc.getContext(), maybeKey.value());
}

} // namespace TFHE
} // namespace toruslang
} // namespace mlir
