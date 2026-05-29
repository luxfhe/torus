// Part of the Concrete Compiler Project, under the BSD3 License with Zama
// Exceptions. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#include "toruslang/Dialect/Concrete/IR/ConcreteDialect.h"
#include "toruslang/Dialect/Concrete/IR/ConcreteOps.h"
#include "toruslang/Dialect/SDFG/IR/SDFGDialect.h"
#include "toruslang/Dialect/SDFG/IR/SDFGOps.h"
#include "toruslang/Dialect/SDFG/Interfaces/SDFGConvertibleInterface.h"
#include "llvm/ADT/SmallVector.h"

namespace mlir {
namespace toruslang {
namespace SDFG {
namespace {
char add_eint[] = "add_eint";
char add_eint_int[] = "add_eint_int";
char mul_eint_int[] = "mul_eint_int";
char neg_eint[] = "neg_eint";
char keyswitch[] = "keyswitch";
char bootstrap[] = "bootstrap";

char batched_add_eint[] = "batched_add_eint";
char batched_add_eint_int[] = "batched_add_eint_int";
char batched_add_eint_int_cst[] = "batched_add_eint_int_cst";
char batched_mul_eint_int[] = "batched_mul_eint_int";
char batched_mul_eint_int_cst[] = "batched_mul_eint_int_cst";
char batched_neg_eint[] = "batched_neg_eint";
char batched_keyswitch[] = "batched_keyswitch";
char batched_bootstrap[] = "batched_bootstrap";
char batched_mapped_bootstrap[] = "batched_mapped_bootstrap";
} // namespace

template <typename Op, char const *processName, bool copyAttributes = false>
struct ReplaceWithProcessSDFGConversionInterface
    : public SDFGConvertibleOpInterface::ExternalModel<
          ReplaceWithProcessSDFGConversionInterface<Op, processName,
                                                    copyAttributes>,
          Op> {
  MakeProcess convert(Operation *op, mlir::ImplicitLocOpBuilder &builder,
                      ::mlir::Value dfg, ::mlir::ValueRange inStreams,
                      ::mlir::ValueRange outStreams) const {
    llvm::SmallVector<mlir::Value> streams = llvm::to_vector(inStreams);
    streams.append(outStreams.begin(), outStreams.end());
    MakeProcess process = builder.create<MakeProcess>(
        *symbolizeProcessKind(processName), dfg, streams);

    if (copyAttributes) {
      auto outType =
          op->getResult(0).getType().dyn_cast_or_null<mlir::TensorType>();
      auto outSize = outType.getDimSize(outType.getRank() - 1);
      auto attrList = mlir::NamedAttrList(op->getAttrs());
      attrList.append("output_size", builder.getI32IntegerAttr(outSize));
      llvm::SmallVector<mlir::NamedAttribute> combinedAttrs =
          llvm::to_vector(attrList);

      for (mlir::NamedAttribute attr : process->getAttrs()) {
        combinedAttrs.push_back(attr);
      }

      process->setAttrs(combinedAttrs);
    }

    return process;
  }
};

void registerSDFGConvertibleOpInterfaceExternalModels(
    DialectRegistry &registry) {
  registry.addExtension(+[](MLIRContext *ctx,
                            Concrete::ConcreteDialect *dialect) {
    mlir::toruslang::Concrete::AddLweTensorOp::attachInterface<
        ReplaceWithProcessSDFGConversionInterface<
            mlir::toruslang::Concrete::AddLweTensorOp, add_eint>>(*ctx);

    mlir::toruslang::Concrete::AddPlaintextLweTensorOp::attachInterface<
        ReplaceWithProcessSDFGConversionInterface<
            mlir::toruslang::Concrete::AddPlaintextLweTensorOp,
            add_eint_int>>(*ctx);

    mlir::toruslang::Concrete::MulCleartextLweTensorOp::attachInterface<
        ReplaceWithProcessSDFGConversionInterface<
            mlir::toruslang::Concrete::MulCleartextLweTensorOp,
            mul_eint_int>>(*ctx);

    mlir::toruslang::Concrete::NegateLweTensorOp::attachInterface<
        ReplaceWithProcessSDFGConversionInterface<
            mlir::toruslang::Concrete::NegateLweTensorOp, neg_eint>>(*ctx);

    mlir::toruslang::Concrete::KeySwitchLweTensorOp::attachInterface<
        ReplaceWithProcessSDFGConversionInterface<
            mlir::toruslang::Concrete::KeySwitchLweTensorOp, keyswitch,
            true>>(*ctx);

    mlir::toruslang::Concrete::BootstrapLweTensorOp::attachInterface<
        ReplaceWithProcessSDFGConversionInterface<
            mlir::toruslang::Concrete::BootstrapLweTensorOp, bootstrap,
            true>>(*ctx);

    mlir::toruslang::Concrete::BatchedAddLweTensorOp::attachInterface<
        ReplaceWithProcessSDFGConversionInterface<
            mlir::toruslang::Concrete::BatchedAddLweTensorOp,
            batched_add_eint>>(*ctx);
    mlir::toruslang::Concrete::BatchedAddPlaintextLweTensorOp::
        attachInterface<ReplaceWithProcessSDFGConversionInterface<
            mlir::toruslang::Concrete::BatchedAddPlaintextLweTensorOp,
            batched_add_eint_int>>(*ctx);
    mlir::toruslang::Concrete::BatchedAddPlaintextCstLweTensorOp::
        attachInterface<ReplaceWithProcessSDFGConversionInterface<
            mlir::toruslang::Concrete::BatchedAddPlaintextCstLweTensorOp,
            batched_add_eint_int_cst>>(*ctx);
    mlir::toruslang::Concrete::BatchedMulCleartextLweTensorOp::
        attachInterface<ReplaceWithProcessSDFGConversionInterface<
            mlir::toruslang::Concrete::BatchedMulCleartextLweTensorOp,
            batched_mul_eint_int>>(*ctx);
    mlir::toruslang::Concrete::BatchedMulCleartextCstLweTensorOp::
        attachInterface<ReplaceWithProcessSDFGConversionInterface<
            mlir::toruslang::Concrete::BatchedMulCleartextCstLweTensorOp,
            batched_mul_eint_int_cst>>(*ctx);
    mlir::toruslang::Concrete::BatchedNegateLweTensorOp::attachInterface<
        ReplaceWithProcessSDFGConversionInterface<
            mlir::toruslang::Concrete::BatchedNegateLweTensorOp,
            batched_neg_eint>>(*ctx);
    mlir::toruslang::Concrete::BatchedKeySwitchLweTensorOp::attachInterface<
        ReplaceWithProcessSDFGConversionInterface<
            mlir::toruslang::Concrete::BatchedKeySwitchLweTensorOp,
            batched_keyswitch, true>>(*ctx);
    mlir::toruslang::Concrete::BatchedBootstrapLweTensorOp::attachInterface<
        ReplaceWithProcessSDFGConversionInterface<
            mlir::toruslang::Concrete::BatchedBootstrapLweTensorOp,
            batched_bootstrap, true>>(*ctx);
    mlir::toruslang::Concrete::BatchedMappedBootstrapLweTensorOp::
        attachInterface<ReplaceWithProcessSDFGConversionInterface<
            mlir::toruslang::Concrete::BatchedMappedBootstrapLweTensorOp,
            batched_mapped_bootstrap, true>>(*ctx);
  });
}
} // namespace SDFG
} // namespace toruslang
} // namespace mlir
