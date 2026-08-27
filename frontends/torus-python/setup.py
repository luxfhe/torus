import os
import re
import setuptools

from setuptools import Extension
from setuptools.command.build_ext import build_ext


def read(file):
    return open(os.path.join(os.path.dirname(__file__), file)).read()


def version():
    return re.match(r"__version__ = \"(?P<version>.+)\"", read("version.txt")).group("version")


def bindings_directory():
    path = os.environ.get("COMPILER_BUILD_DIRECTORY")
    if path is None or path == "":
        raise RuntimeError("COMPILER_BUILD_DIRECTORY is not set")
    return os.path.relpath(path) + "/tools/toruslang/python_packages/toruslang_core"


class MakeExtension(Extension):
    def __init__(self, name):
        Extension.__init__(self, name, sources=[])


class MakeBuild(build_ext):
    def run(self):
        pass


def read_requirements(*filenames):
    return [
        dependency
        for filename in filenames
        for dependency in read(filename).split("\n")
        if dependency.strip() != ""
    ]

# The distribution's identity — name, description, licence, authors, keywords,
# classifiers, readme, requires-python — is declared once, in pyproject.toml.
# It named this "torus-python" here while pyproject named it "torus-fhe", which
# is two names for one distribution and, with PEP 621 metadata present, a build
# error rather than a preference.
#
# What is left is what pyproject marks dynamic and cannot compute: the version,
# the requirement files, and the packages, which depend on where the native
# bindings were built.
setuptools.setup(

    version=version(),

    setup_requires=["wheel"],
    install_requires=read_requirements("requirements.txt"),
    extras_require={
        "dev": read_requirements("requirements.dev.txt", "requirements.extra-full.txt"),
        "full": read_requirements("requirements.extra-full.txt"),
    },
    # The sources moved to torus/ with the rebrand; this still addressed the
    # directory they were moved out of, so the frontend built without the very
    # package it exists to ship. torus.fhe needs its own entry: the root maps to
    # the bindings tree, and this package is not in it.
    package_dir={
        "torus.fhe": "./torus/fhe",
        "": bindings_directory(),
    },
    packages=setuptools.find_namespace_packages(
        where=".",
        include=["torus", "torus.fhe", "torus.fhe.*"],
    ) + setuptools.find_namespace_packages(
        where=bindings_directory(),
        include=["torus.compiler", "torus.compiler.*"],
    ) + setuptools.find_namespace_packages(
        where=bindings_directory(),
        include=["torus.lang", "torus.lang.*"],
    ) + setuptools.find_namespace_packages(
        where=bindings_directory(),
        include=["mlir", "mlir.*"],
    ),

    include_package_data=True,
    package_data={"": ["*.so", "*.dylib"]},

    ext_modules=[MakeExtension("python-bindings")],
    cmdclass=dict(build_ext=MakeBuild),
    zip_safe=False,

)
