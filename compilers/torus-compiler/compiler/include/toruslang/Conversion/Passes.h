// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_TRANSFORMS_PASSES_H
#define TORUSLANG_TRANSFORMS_PASSES_H

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"

#include "toruslang/Conversion/TorusToCAPI/Pass.h"
#include "toruslang/Conversion/ExtractSDFGOps/Pass.h"
#include "toruslang/Conversion/FHETensorOpsToLinalg/Pass.h"
#include "toruslang/Conversion/FHEToTFHECrt/Pass.h"
#include "toruslang/Conversion/FHEToTFHEScalar/Pass.h"
#include "toruslang/Conversion/LinalgExtras/Passes.h"
#include "toruslang/Conversion/MLIRLowerableDialectsToLLVM/Pass.h"
#include "toruslang/Conversion/SDFGToStreamEmulator/Pass.h"
#include "toruslang/Conversion/SimulateTFHE/Pass.h"
#include "toruslang/Conversion/TFHEGlobalParametrization/Pass.h"
#include "toruslang/Conversion/TFHEKeyNormalization/Pass.h"
#include "toruslang/Conversion/TFHEToTorus/Pass.h"
#include "toruslang/Conversion/TracingToCAPI/Pass.h"
#include "toruslang/Dialect/Torus/IR/TorusDialect.h"
#include "toruslang/Dialect/FHE/IR/FHEDialect.h"
#include "toruslang/Dialect/SDFG/IR/SDFGDialect.h"
#include "toruslang/Dialect/TFHE/IR/TFHEDialect.h"
#include "toruslang/Dialect/Tracing/IR/TracingDialect.h"

#define GEN_PASS_CLASSES
#include "toruslang/Conversion/Passes.h.inc"

#endif
