// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_FHE_IR_FHEOPS_H
#define TORUSLANG_DIALECT_FHE_IR_FHEOPS_H

#include <mlir/IR/Builders.h>
#include <mlir/IR/BuiltinOps.h>
#include <mlir/IR/BuiltinTypes.h>
#include <mlir/Interfaces/ControlFlowInterfaces.h>
#include <mlir/Interfaces/SideEffectInterfaces.h>

#include "toruslang/Dialect/FHE/IR/FHEAttrs.h"
#include "toruslang/Dialect/FHE/IR/FHETypes.h"

namespace mlir {
namespace toruslang {
namespace FHE {

bool verifyEncryptedIntegerInputAndResultConsistency(
    Operation &op, FheIntegerInterface &input, FheIntegerInterface &result);

// Checks the consistency between two integer inputs of an operation
bool verifyEncryptedIntegerInputsConsistency(mlir::Operation &op,
                                             FheIntegerInterface &a,
                                             FheIntegerInterface &b);

/// Shared error message for all ApplyLookupTable variant Op (several Dialect)
/// E.g. FHE.apply_lookup_table(input, lut)
/// Message when the lut tensor has an invalid size,
/// i.e. it cannot accommodate the input elements bitwidth
template <class Op>
void emitErrorBadLutSize(Op &op, std::string lutName, std::string inputName,
                         int expectedSize, int bitWidth) {
  auto s = op.emitOpError();
  s << ": `" << lutName << "` (operand #2)"
    << " inner dimension should have size " << expectedSize << "(=2^"
    << bitWidth << ") to match " << "`" << inputName << "` (operand #1)"
    << " elements bitwidth (" << bitWidth << ")";
}

} // namespace FHE
} // namespace toruslang
} // namespace mlir

#define GET_OP_CLASSES
#include "toruslang/Dialect/FHE/IR/FHEOps.h.inc"

#endif
