"""
Tests of `version` module.
"""

from torus import fhe


def test_version_exists():
    """
    Test `torus.fhe` has `__version__`.
    """

    assert hasattr(fhe, "__version__")
