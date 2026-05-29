# Python Frontend

## Installation for end-users

End-users should install `torus-python` using `pip`:

```shell
pip install torus-python
```

**Note:** Not all versions are available on PyPI. If you need a version that is not on PyPI (including nightly releases), you can install it from our package index by adding `--extra-index-url https://pypi.luxfhe.com/cpu/`. GPU wheels are also available under `https://pypi.luxfhe.com/gpu/` (check `https://pypi.luxfhe.com/` for all available platforms).

## Setup for development

Developers that want to contribute to the Torus-Python project can use the following
approach to setup their environment.

```shell
# clone the repository
git clone https://github.com/luxfhe/torus.git --recursive
cd concrete

# create virtual environment
cd frontends/torus-python
make venv

# activate virtual environment
source .venv/bin/activate

# build the compiler bindings
cd ../../compilers/torus-compiler/compiler
make python-bindings

# set bindings build directory as an environment variable
# *** NOTE ***: You must use the Release build of the compiler! 
# For now, the Debug build is not compatible with torus-python
export COMPILER_BUILD_DIRECTORY=$(pwd)/build
echo "export COMPILER_BUILD_DIRECTORY=$(pwd)/build" >> ~/.bashrc

# run tests
cd ../../../frontends/torus-python
make pytest
```

### VSCode setup

Alternatively you can use VSCode to develop Torus-Python:

Suppose the compiler bindings were built in `/home/lux/concrete/compilers/torus-compiler/compiler/build`:

- Create a `.env` file in the torus-python root directory
- Determine the absolute path of the local compiler repository, e.g. `/home/lux/concrete`. Replace this with your 
path in the following two lines
- Add to it `PYTHONPATH=$(PYTHON_PATH):/home/lux/concrete/compilers/torus-compiler/compiler/build/tools/toruslang/python_packages/toruslang_core/`
- Add to it `LD_PRELOAD=/home/lux/concrete/compilers/torus-compiler/compiler/build/lib/libToruslangRuntime.so`

You can now configure `pytest` in VScode and run the tests using the graphical interface.
