// Part of the Concrete Compiler Project, under the BSD3 License with Lux Industries
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_FHE_ANALYSIS_CONCRETE_OPTIMIZER_H
#define TORUSLANG_DIALECT_FHE_ANALYSIS_CONCRETE_OPTIMIZER_H

#include <map>
#include <mlir/Pass/Pass.h>

#include "torus-optimizer.hpp"

#include "toruslang/Support/V0Parameters.h"

namespace mlir {
namespace toruslang {

namespace optimizer {
std::unique_ptr<mlir::Pass> createDagPass(optimizer::Config config,
                                          concrete_optimizer::Dag &dag);

void applyCompositionRules(optimizer::Config config,
                           concrete_optimizer::Dag &dag);

} // namespace optimizer
} // namespace toruslang
} // namespace mlir

#endif
