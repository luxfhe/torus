"""
Declaration of `ClientSpecs` class.
"""

# pylint: disable=import-error,no-member,no-name-in-module
import json
from typing import Any

# mypy: disable-error-code=attr-defined
from torus.compiler import ProgramInfo

# pylint: enable=import-error,no-member,no-name-in-module


class ClientSpecs:
    """
    ClientSpecs class, to create Client objects.
    """

    program_info: ProgramInfo

    def __init__(self, program_info: ProgramInfo):
        self.program_info = program_info

    def __eq__(self, other: Any):  # pragma: no cover
        return self.program_info.serialize() == other.program_info.serialize()

    def serialize(self) -> bytes:
        """
        Serialize client specs into bytes.

        Returns:
            bytes:
                serialized client specs
        """
        return self.program_info.serialize()

    @staticmethod
    def deserialize(serialized_client_specs: bytes) -> "ClientSpecs":
        """
        Create client specs from bytes.

        Args:
            serialized_client_specs (bytes):
                client specs to deserialize

        Returns:
            ClientSpecs:
                deserialized client specs
        """
        return ClientSpecs(ProgramInfo.deserialize(serialized_client_specs))
