// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_TFHE_IR_TFHEPARAMETERS_H
#define TORUSLANG_DIALECT_TFHE_IR_TFHEPARAMETERS_H

#include "llvm/ADT/TypeSwitch.h"
#include <mlir/Dialect/Func/IR/FuncOps.h>
#include <mlir/IR/BuiltinOps.h>
#include <mlir/IR/BuiltinTypes.h>
#include <mlir/IR/DialectImplementation.h>
#include <variant>

namespace mlir {
namespace toruslang {
namespace TFHE {

/// A placeholder.
struct GLWESecretKeyNone {};
llvm::raw_ostream &operator<<(llvm::raw_ostream &OS,
                              const GLWESecretKeyNone sk);

// The key was parameterized.
struct GLWESecretKeyParameterized {
  uint64_t dimension;
  uint64_t polySize;
  uint64_t identifier;
  bool operator==(const GLWESecretKeyParameterized other) const;
};
llvm::raw_ostream &operator<<(llvm::raw_ostream &OS,
                              const GLWESecretKeyParameterized sk);

// The key was normalized
struct GLWESecretKeyNormalized {
  uint64_t dimension;
  uint64_t polySize;
  uint64_t index;
  bool operator==(const GLWESecretKeyNormalized other) const;
};
llvm::raw_ostream &operator<<(llvm::raw_ostream &OS,
                              const GLWESecretKeyNormalized sk);

/// A sum type parameter representing GLWE secret keys in different states.
struct GLWESecretKey {
  std::variant<GLWESecretKeyNone, GLWESecretKeyParameterized,
               GLWESecretKeyNormalized>
      inner;

  static GLWESecretKey newNone();
  static GLWESecretKey newParameterized(uint64_t dimension, uint64_t polySize,
                                        uint64_t identifier);
  static GLWESecretKey newNormalized(uint64_t dimension, uint64_t polySize,
                                     uint64_t index);
  bool operator==(const GLWESecretKey other) const;
  bool operator!=(const GLWESecretKey other) const;
  template <typename V> bool is();
  bool isNone();
  bool isParameterized();
  bool isNormalized();
  template <typename V> std::optional<V> get();
  std::optional<GLWESecretKeyNone> getNone();
  std::optional<GLWESecretKeyParameterized> getParameterized();
  std::optional<GLWESecretKeyNormalized> getNormalized();
};

llvm::hash_code hash_value(const GLWESecretKey &key);
llvm::raw_ostream &operator<<(llvm::raw_ostream &OS, const GLWESecretKey sk);

} // namespace TFHE
} // namespace toruslang
} // namespace mlir

namespace mlir {

AsmPrinter &operator<<(AsmPrinter &p,
                       mlir::toruslang::TFHE::GLWESecretKey key);

template <> struct FieldParser<mlir::toruslang::TFHE::GLWESecretKey> {
  static FailureOr<mlir::toruslang::TFHE::GLWESecretKey>
  parse(AsmParser &parser);
};
} // namespace mlir

#endif
