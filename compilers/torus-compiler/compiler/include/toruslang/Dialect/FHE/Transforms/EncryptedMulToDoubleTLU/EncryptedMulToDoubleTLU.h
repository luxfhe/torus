// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_FHE_ENCRYPTED_MUL_TO_DOUBLE_TLU_PASS_H
#define TORUSLANG_FHE_ENCRYPTED_MUL_TO_DOUBLE_TLU_PASS_H

#include <toruslang/Dialect/FHE/IR/FHEDialect.h>
#include <mlir/Dialect/Func/IR/FuncOps.h>
#include <mlir/Pass/Pass.h>

#define GEN_PASS_CLASSES

#include <toruslang/Dialect/FHE/Transforms/EncryptedMulToDoubleTLU/EncryptedMulToDoubleTLU.h.inc>

namespace mlir {
namespace toruslang {
std::unique_ptr<mlir::OperationPass<mlir::func::FuncOp>>
createEncryptedMulToDoubleTLUPass();
} // namespace toruslang
} // namespace mlir

#endif
