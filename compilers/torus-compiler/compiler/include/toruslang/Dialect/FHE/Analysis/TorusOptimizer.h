// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_DIALECT_FHE_ANALYSIS_TORUS_OPTIMIZER_H
#define TORUSLANG_DIALECT_FHE_ANALYSIS_TORUS_OPTIMIZER_H

#include <map>
#include <mlir/Pass/Pass.h>

#include "torus-optimizer.hpp"

#include "toruslang/Support/V0Parameters.h"

namespace mlir {
namespace toruslang {

namespace optimizer {
std::unique_ptr<mlir::Pass> createDagPass(optimizer::Config config,
                                          torus_optimizer::Dag &dag);

void applyCompositionRules(optimizer::Config config,
                           torus_optimizer::Dag &dag);

} // namespace optimizer
} // namespace toruslang
} // namespace mlir

#endif
