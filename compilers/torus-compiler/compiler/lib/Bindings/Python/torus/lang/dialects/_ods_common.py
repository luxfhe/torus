#  Part of the Torus Compiler Project, under the BSD 3-Clause Clear License.
#  See https://github.com/luxfhe/torus/blob/main/LICENSE.txt for license information.

# We need this helpers from the mlir bindings, they are used in the generated files
from mlir.dialects._ods_common import (
    _cext,
    segmented_accessor,
    equally_sized_accessor,
    extend_opview_class,
    get_default_loc_context,
    get_op_result_or_value,
    get_op_results_or_values,
)
