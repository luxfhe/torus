"""
Tests of `Node` class.
"""

import numpy as np
import pytest

from torus.fhe.dtypes import UnsignedInteger
from torus.fhe.representation import Node
from torus.fhe.values import (
    ClearScalar,
    ClearTensor,
    EncryptedScalar,
    EncryptedTensor,
    ValueDescription,
)


@pytest.mark.parametrize(
    "constant,expected_error,expected_message",
    [
        pytest.param(
            "abc",
            ValueError,
            "Constant 'abc' is not supported",
        ),
    ],
)
def test_node_bad_constant(constant, expected_error, expected_message):
    """
    Test `constant` function of `Node` class with bad parameters.
    """

    with pytest.raises(expected_error) as excinfo:
        Node.constant(constant)

    assert str(excinfo.value) == expected_message



def test_node_bad_call(node, args, expected_error, expected_message):
    """
    Test `__call__` method of `Node` class.
    """

    with pytest.raises(expected_error) as excinfo:
        node(*args)

    assert str(excinfo.value) == expected_message


@pytest.mark.parametrize(
    "node,predecessors,expected_result",
    [
        pytest.param(
            Node.constant(1),
            [],
            "1",
        ),
        pytest.param(
            Node.input("x", EncryptedScalar(UnsignedInteger(3))),
            [],
            "x",
        ),
        pytest.param(
            Node.generic(
                name="tlu",
                inputs=[
                    EncryptedTensor(UnsignedInteger(3), shape=(3, 2)),
                ],
                output=EncryptedTensor(UnsignedInteger(3), shape=(3, 2)),
                operation=lambda x, table: table[x],
                kwargs={"table": np.array([4, 1, 3, 2])},
            ),
            ["%0"],
            "tlu(%0, table=[4 1 3 2])",
        ),
        pytest.param(
            Node.generic(
                name="index_static",
                inputs=[EncryptedTensor(UnsignedInteger(3), shape=(3,))],
                output=EncryptedTensor(UnsignedInteger(3), shape=(3,)),
                operation=lambda x: x[slice(None, None, -1)],
                kwargs={"index": (slice(None, None, -1),)},
            ),
            ["%0"],
            "%0[::-1]",
        ),
        pytest.param(
            Node.generic(
                name="concatenate",
                inputs=[
                    EncryptedTensor(UnsignedInteger(3), shape=(3, 2)),
                    EncryptedTensor(UnsignedInteger(3), shape=(3, 2)),
                    EncryptedTensor(UnsignedInteger(3), shape=(3, 2)),
                ],
                output=EncryptedTensor(UnsignedInteger(3), shape=(3, 6)),
                operation=lambda *args, **kwargs: np.concatenate(tuple(args), **kwargs),
                kwargs={"axis": 1},
            ),
            ["%0", "%1", "%2"],
            "concatenate((%0, %1, %2), axis=1)",
        ),
        pytest.param(
            Node.generic(
                name="array",
                inputs=[
                    EncryptedScalar(UnsignedInteger(3)),
                    ClearScalar(UnsignedInteger(3)),
                    ClearScalar(UnsignedInteger(3)),
                    EncryptedScalar(UnsignedInteger(3)),
                ],
                output=EncryptedTensor(UnsignedInteger(3), shape=(2, 2)),
                operation=lambda *args: np.array(args).reshape((2, 2)),
            ),
            ["%0", "%1", "%2", "%3"],
            "array([[%0, %1], [%2, %3]])",
        ),
        pytest.param(
            Node.generic(
                name="assign_static",
                inputs=[EncryptedTensor(UnsignedInteger(3), shape=(3, 4))],
                output=EncryptedTensor(UnsignedInteger(3), shape=(3, 4)),
                operation=lambda *args: args,
                kwargs={"index": (1, 2)},
            ),
            ["%0", "%1"],
            "(%0[1, 2] = %1)",
        ),
        pytest.param(
            Node.generic(
                name="index_dynamic",
                inputs=[
                    EncryptedTensor(UnsignedInteger(5), shape=(8,)),
                    ClearTensor(UnsignedInteger(3), shape=(3,)),
                ],
                output=EncryptedTensor(UnsignedInteger(5), shape=(3,)),
                operation=lambda *args: args,
                kwargs={"static_indices": (None,)},
            ),
            ["%0", "%1"],
            "%0[%1]",
        ),
        pytest.param(
            Node.generic(
                name="index_dynamic",
                inputs=[
                    EncryptedTensor(UnsignedInteger(5), shape=(8, 4)),
                    ClearTensor(UnsignedInteger(3), shape=(3,)),
                ],
                output=EncryptedTensor(UnsignedInteger(5), shape=(3,)),
                operation=lambda *args: args,
                kwargs={"static_indices": (None, 0)},
            ),
            ["%0", "%1"],
            "%0[%1, 0]",
        ),
        pytest.param(
            Node.generic(
                name="index_dynamic",
                inputs=[
                    EncryptedTensor(UnsignedInteger(5), shape=(8, 4)),
                    ClearTensor(UnsignedInteger(2), shape=(3,)),
                ],
                output=EncryptedTensor(UnsignedInteger(5), shape=(3,)),
                operation=lambda *args: args,
                kwargs={"static_indices": (0, None)},
            ),
            ["%0", "%1"],
            "%0[0, %1]",
        ),
        pytest.param(
            Node.generic(
                name="index_dynamic",
                inputs=[
                    EncryptedTensor(UnsignedInteger(5), shape=(8, 4)),
                    ClearTensor(UnsignedInteger(3), shape=(3,)),
                    ClearTensor(UnsignedInteger(2), shape=(3,)),
                ],
                output=EncryptedTensor(UnsignedInteger(5), shape=(3,)),
                operation=lambda *args: args,
                kwargs={"static_indices": (None, None)},
            ),
            ["%0", "%1", "%2"],
            "%0[%1, %2]",
        ),
    ],
)
def test_node_format(node, predecessors, expected_result):
    """
    Test `format` method of `Node` class.
    """

    assert node.format(predecessors) == expected_result


@pytest.mark.parametrize(
    "node,expected_result",
    [
        pytest.param(
            Node.constant(1),
            "1",
        ),
        pytest.param(
            Node.input("x", EncryptedScalar(UnsignedInteger(3))),
            "x",
        ),
        pytest.param(
            Node.generic(
                name="tlu",
                inputs=[
                    EncryptedTensor(UnsignedInteger(3), shape=(3, 2)),
                ],
                output=EncryptedTensor(UnsignedInteger(3), shape=(3, 2)),
                operation=lambda x, table: table[x],
                kwargs={"table": np.array([4, 1, 3, 2])},
            ),
            "tlu",
        ),
        pytest.param(
            Node.generic(
                name="concatenate",
                inputs=[
                    EncryptedTensor(UnsignedInteger(3), shape=(3, 2)),
                    EncryptedTensor(UnsignedInteger(3), shape=(3, 2)),
                    EncryptedTensor(UnsignedInteger(3), shape=(3, 2)),
                ],
                output=EncryptedTensor(UnsignedInteger(3), shape=(3, 6)),
                operation=lambda *args, **kwargs: np.concatenate(tuple(args), **kwargs),
                kwargs={"axis": -1},
            ),
            "concatenate",
        ),
        pytest.param(
            Node.generic(
                name="index_static",
                inputs=[EncryptedTensor(UnsignedInteger(3), shape=(3, 4))],
                output=EncryptedTensor(UnsignedInteger(3), shape=()),
                operation=lambda *args: args,
                kwargs={"index": (1, 2)},
            ),
            "□[1, 2]",
        ),
        pytest.param(
            Node.generic(
                name="assign_static",
                inputs=[EncryptedTensor(UnsignedInteger(3), shape=(3, 4))],
                output=EncryptedTensor(UnsignedInteger(3), shape=(3, 4)),
                operation=lambda *args: args,
                kwargs={"index": (1, 2)},
            ),
            "□[1, 2] = □",
        ),
        pytest.param(
            Node.generic(
                name="index_dynamic",
                inputs=[
                    EncryptedTensor(UnsignedInteger(5), shape=(8,)),
                    ClearTensor(UnsignedInteger(3), shape=(3,)),
                ],
                output=EncryptedTensor(UnsignedInteger(5), shape=(3,)),
                operation=lambda *args: args,
                kwargs={"static_indices": (None,)},
            ),
            "□[□]",
        ),
        pytest.param(
            Node.generic(
                name="index_dynamic",
                inputs=[
                    EncryptedTensor(UnsignedInteger(5), shape=(8, 4)),
                    ClearTensor(UnsignedInteger(3), shape=(3,)),
                ],
                output=EncryptedTensor(UnsignedInteger(5), shape=(3,)),
                operation=lambda *args: args,
                kwargs={"static_indices": (None, 0)},
            ),
            "□[□, 0]",
        ),
        pytest.param(
            Node.generic(
                name="index_dynamic",
                inputs=[
                    EncryptedTensor(UnsignedInteger(5), shape=(8, 4)),
                    ClearTensor(UnsignedInteger(2), shape=(3,)),
                ],
                output=EncryptedTensor(UnsignedInteger(5), shape=(3,)),
                operation=lambda *args: args,
                kwargs={"static_indices": (0, None)},
            ),
            "□[0, □]",
        ),
        pytest.param(
            Node.generic(
                name="index_dynamic",
                inputs=[
                    EncryptedTensor(UnsignedInteger(5), shape=(8, 4)),
                    ClearTensor(UnsignedInteger(3), shape=(3,)),
                    ClearTensor(UnsignedInteger(2), shape=(3,)),
                ],
                output=EncryptedTensor(UnsignedInteger(5), shape=(3,)),
                operation=lambda *args: args,
                kwargs={"static_indices": (None, None)},
            ),
            "□[□, □]",
        ),
        pytest.param(
            Node.generic(
                name="assign_dynamic",
                inputs=[
                    EncryptedTensor(UnsignedInteger(5), shape=(8,)),
                    ClearScalar(UnsignedInteger(3)),
                    ClearScalar(UnsignedInteger(5)),
                ],
                output=EncryptedTensor(UnsignedInteger(5), shape=(8,)),
                operation=lambda *args: args,
                kwargs={"static_indices": (None,)},
            ),
            "□[□] = □",
        ),
        pytest.param(
            Node.generic(
                name="assign_dynamic",
                inputs=[
                    EncryptedTensor(UnsignedInteger(5), shape=(8, 4)),
                    ClearScalar(UnsignedInteger(3)),
                    ClearScalar(UnsignedInteger(5)),
                ],
                output=EncryptedTensor(UnsignedInteger(5), shape=(8, 4)),
                operation=lambda *args: args,
                kwargs={"static_indices": (None, 0)},
            ),
            "□[□, 0] = □",
        ),
        pytest.param(
            Node.generic(
                name="assign_dynamic",
                inputs=[
                    EncryptedTensor(UnsignedInteger(5), shape=(8, 4)),
                    ClearScalar(UnsignedInteger(3)),
                    ClearScalar(UnsignedInteger(5)),
                ],
                output=EncryptedTensor(UnsignedInteger(5), shape=(8, 4)),
                operation=lambda *args: args,
                kwargs={"static_indices": (0, None)},
            ),
            "□[0, □] = □",
        ),
        pytest.param(
            Node.generic(
                name="assign_dynamic",
                inputs=[
                    EncryptedTensor(UnsignedInteger(5), shape=(8, 4)),
                    ClearScalar(UnsignedInteger(3)),
                    ClearScalar(UnsignedInteger(2)),
                    ClearScalar(UnsignedInteger(5)),
                ],
                output=EncryptedTensor(UnsignedInteger(5), shape=(8, 4)),
                operation=lambda *args: args,
                kwargs={"static_indices": (None, None)},
            ),
            "□[□, □] = □",
        ),
    ],
)
def test_node_label(node, expected_result):
    """
    Test `label` method of `Node` class.
    """

    assert node.label() == expected_result
