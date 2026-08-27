// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "toruslang/Dialect/FHE/Interfaces/FHEInterfacesInstances.h"
#include "toruslang/Dialect/FHE/IR/FHEDialect.h"
#include "toruslang/Dialect/FHE/Interfaces/FHEInterfaces.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"

namespace mlir {
namespace toruslang {
namespace FHE {

using namespace mlir::tensor;

void registerFheInterfacesExternalModels(DialectRegistry &registry) {
  registry.addExtension(+[](MLIRContext *ctx, TensorDialect *dialect) {
    ExtractOp::attachInterface<UnaryEint>(*ctx);
    InsertSliceOp::attachInterface<MaxNoise>(*ctx);
    InsertOp::attachInterface<MaxNoise>(*ctx);
    ParallelInsertSliceOp::attachInterface<MaxNoise>(*ctx);
  });
}
} // namespace FHE
} // namespace toruslang
} // namespace mlir
