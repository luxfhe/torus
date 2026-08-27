# Project layout

## Torus layout

Torus is a modular framework composed by sub-projects using different technologies, all having theirs own build system and test suite. Each sub-project have is own README that explain how to setup the developer environment, how to build it and how to run tests commands.

Torus is made of 4 main categories of sub-project that are organized in subdirectories from the root of the Torus repo:

* `frontends` contains **high-level transpilers** that target end users developers who want to use the Torus stack easily from their usual environment. There are for now only one frontend provided by the Torus project: a Python frontend named `torus-python`.
* `compilers` contains the sub-projects in charge of actually solving the compilation problem of an high-level abstraction of FHE to an actual executable. `torus-optimizer` is a Rust based project that solves the optimization problems of an FHE dag to a TFHE dag and `torus-compiler` which use `torus-optimizer` is an end-to-end MLIR-based compiler that takes a crypto free FHE dialect and generates compilation artifacts both for the client and the server. `torus-compiler` project provide in addition of the compilation engine, a client and server library in order to easily play with the compilation artifacts to implement a client and server protocol.
* `backends` contains CAPI that can be called by the `torus-compiler` runtime to perform the cryptographic operations. There are currently two backends:
  * `torus-cpu`, using Lux-FHE that implement the fastest implementation of TFHE on CPU.
  * `torus-cuda` that provides a GPU acceleration of TFHE primitives.
* `tools` are basically every other sub-projects that cannot be classified in the three previous categories and which are used as a common support by the others.

## Torus Python layout

The module structure of **Torus Python**. You are encouraged to check individual `.py` files to learn more.

* torus
  * fhe
    * **dtypes:** data type specifications (e.g., int4, uint5, float32)
    * **values:** value specifications (i.e., data type + shape + encryption status)
    * **representation:** representation of computation (e.g., computation graphs, nodes)
    * **tracing:** tracing of python functions
    * **extensions:** custom functionality (see [Extensions](../core-features/extensions.md))
    * **mlir:** computation graph to mlir conversion
    * **compilation:** configuration, compiler, artifacts, circuit, client/server, and anything else related to compilation
