// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_RT_TYPEINFERENCE_H
#define TORUSLANG_DIALECT_RT_TYPEINFERENCE_H

#include <toruslang/Analysis/TypeInferenceAnalysis.h>
#include <toruslang/Dialect/RT/IR/RTTypes.h>

namespace mlir {
namespace toruslang {
namespace RT {

template <typename BaseConstraintT, unsigned int leftDepth,
          unsigned int rightDepth>
class SameNestedTypeContraint
    : public SameNestedTypeConstraintBase<BaseConstraintT, leftDepth,
                                          rightDepth> {
public:
  using SameNestedTypeConstraintBase<BaseConstraintT, leftDepth,
                                     rightDepth>::SameNestedTypeConstraintBase;

protected:
  mlir::Type getNestedType(mlir::Type t) override {
    if (toruslang::RT::PointerType ptrt =
            llvm::dyn_cast<toruslang::RT::PointerType>(t)) {
      return ptrt.getElementType();
    } else if (toruslang::RT::FutureType futt =
                   llvm::dyn_cast<toruslang::RT::FutureType>(t)) {
      return futt.getElementType();
    } else {
      return t;
    }
  }

  mlir::Type applyNestedType(mlir::Type nestedType, mlir::Type t) override {
    if (llvm::isa<toruslang::RT::PointerType>(t)) {
      return toruslang::RT::PointerType::get(nestedType);
    } else if (llvm::isa<toruslang::RT::FutureType>(t)) {
      return toruslang::RT::FutureType::get(nestedType);
    } else {
      return t;
    }
  }
};

// Constraint ensuring that two types are identical when the
// indirection through a pointer is stripped. The parameters
// `leftIsPointer` and `rightIsPointer` indicate which types should be
// stripped from the pointer indirection before comparison.
template <typename BaseConstraintT, bool leftIsPointer, bool rightIsPointer>
class SamePointerTypeContraint
    : public SameNestedTypeConstraintBase<
          BaseConstraintT, leftIsPointer ? 1 : 0, rightIsPointer ? 1 : 0> {
public:
  using SameNestedTypeConstraintBase<
      BaseConstraintT, leftIsPointer ? 1 : 0,
      rightIsPointer ? 1 : 0>::SameNestedTypeConstraintBase;

protected:
  mlir::Type getNestedType(mlir::Type t) override {
    toruslang::RT::PointerType ptrt =
        llvm::cast<toruslang::RT::PointerType>(t);
    return ptrt.getElementType();
  }

  mlir::Type applyNestedType(mlir::Type nestedType, mlir::Type t) override {
    if (llvm::isa<toruslang::RT::PointerType>(t)) {
      return toruslang::RT::PointerType::get(nestedType);
    } else {
      return t;
    }
  }
};

// Constraint ensuring that two types are identical when the
// indirection through a future is stripped. The parameters
// `leftIsFuture` and `rightIsFuture` indicate which types should be
// stripped from the future indirection before comparison.
template <typename BaseConstraintT, bool leftIsFuture, bool rightIsFuture>
class SameFutureTypeContraint
    : public SameNestedTypeConstraintBase<BaseConstraintT, leftIsFuture ? 1 : 0,
                                          rightIsFuture ? 1 : 0> {
public:
  using SameNestedTypeConstraintBase<
      BaseConstraintT, leftIsFuture ? 1 : 0,
      rightIsFuture ? 1 : 0>::SameNestedTypeConstraintBase;

protected:
  mlir::Type getNestedType(mlir::Type t) override {
    toruslang::RT::FutureType ptrt =
        llvm::cast<toruslang::RT::FutureType>(t);
    return ptrt.getElementType();
  }

  mlir::Type applyNestedType(mlir::Type nestedType, mlir::Type t) override {
    if (llvm::isa<toruslang::RT::FutureType>(t)) {
      return toruslang::RT::FutureType::get(nestedType);
    } else {
      return t;
    }
  }
};

} // namespace RT
} // namespace toruslang
} // namespace mlir

#endif // TORUSLANG_DIALECT_RT_TYPEINFERENCE_H
