// Part of the Torus Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_SDFG_TRANSFORMS_PASS_H
#define TORUSLANG_SDFG_TRANSFORMS_PASS_H

#include <mlir/Dialect/Func/IR/FuncOps.h>
#include <mlir/Dialect/Linalg/IR/Linalg.h>
#include <mlir/Dialect/MemRef/IR/MemRef.h>
#include <mlir/Dialect/SCF/IR/SCF.h>
#include <mlir/Pass/Pass.h>

#define GEN_PASS_CLASSES
#include <toruslang/Dialect/SDFG/Transforms/Passes.h.inc>

namespace mlir {
namespace toruslang {

std::unique_ptr<mlir::Pass> createSDFGBufferOwnershipPass();

} // namespace toruslang
} // namespace mlir

#endif
