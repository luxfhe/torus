#include "globals.h"
#include "tests_tools/GtestEnvironment.h"

const mlir::toruslang::V0FHEConstraint defaultV0Constraints{1, 1};

testing::Environment *const dfr_env =
    testing::AddGlobalTestEnvironment(new DFREnvironment);
