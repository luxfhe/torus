#!/usr/bin/env bash

set -e

PYTHON=${PYTHON:-python}
PIP=${PIP:-${PYTHON} -m pip}
VENV_DIR=${PWD}/.venv-docs

# Remove old documentation
rm -rf docs/dev/api/*

# Create virtual env and install torus and docs tools
${PYTHON} -m venv "${VENV_DIR}"
source "${VENV_DIR}"/bin/activate
if [ -z "${TORUS_WHEEL}" ]; then 
    echo "You must specify the TORUS_WHEEL environment variable"
    exit 1
fi
${PIP} install ${TORUS_WHEEL}
${PIP} install lazydocs

# Generate the API doc
lazydocs --output-path="./docs/dev/api" --overview-file="README.md" --src-base-url="../../" --no-watermark torus


# Update documentation paths
SED_OPT='-i'
if [ $(uname) == "Darwin" ]; then
    SED_OPT='-i ""'
fi

# Fixing the path issues, to point on files in GitHub
WHICH_PYTHON_VERSION=$(${PYTHON} --version | cut -f 2 -d " " | cut -f 1-2 -d ".")
sed $SED_OPT -e "s@../../.venv-docs/lib.*/python$WHICH_PYTHON_VERSION/site-packages/@../../../compilers/torus-compiler/compiler/lib/Bindings/Python/@g" docs/dev/api/torus.compiler*.md docs/dev/api/torus.lang*.md
sed $SED_OPT -e "s@../../.venv-docs/lib.*/python$WHICH_PYTHON_VERSION/site-packages/@../../frontends/torus-python/@g" docs/dev/api/torus.fhe*.md

# Fixing the links in README.md, which fails (missing .'s for some reason): remove the #headers
sed $SED_OPT -e "s@.md#module-.*)@.md)@g" docs/dev/api/README.md
sed $SED_OPT -e "s@.md#function-.*)@.md)@g" docs/dev/api/README.md
sed $SED_OPT -e "s@.md#class-.*)@.md)@g" docs/dev/api/README.md

# Removed the "object addresses" and "function addresses", since they are not constant
sed $SED_OPT -e "s@object at 0x[a-zA-Z0-9]*@object at ADDRESS@g" docs/*.md
sed $SED_OPT -e "s@object at 0x[a-zA-Z0-9]*@object at ADDRESS@g" docs/*/*.md
sed $SED_OPT -e "s@object at 0x[a-zA-Z0-9]*@object at ADDRESS@g" docs/*/*/*.md

sed $SED_OPT -e "s@function Int at 0x[a-zA-Z0-9]*@function Int at ADDRESS@g" docs/*.md
sed $SED_OPT -e "s@function Int at 0x[a-zA-Z0-9]*@function Int at ADDRESS@g" docs/*/*.md
sed $SED_OPT -e "s@function Int at 0x[a-zA-Z0-9]*@function Int at ADDRESS@g" docs/*/*/*.md

# FIXME: remove this once the PR has been merged once
sed $SED_OPT -e "s@https://github.com/luxfhe.com/torus-compiler-internal/blob/main/LICENSE.txt@https://github.com/luxfhe/torus/blob/main/LICENSE.txt@g" ./docs/dev/api/torus.lang.dialects.md ./docs/dev/api/torus.compiler.md ./docs/dev/api/torus.lang.md

# Create the patch file
git add -N docs/dev/api/*
git diff docs &> docs.patch

# Was there changes?
if [ ! -s docs.patch ]; then
    echo "The documentation us up to date, congrats."
    exit 0
else
    echo "There is a difference in the docs, please commit the changes, here the change:"
    cat docs.patch
    exit 1
fi

