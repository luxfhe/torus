# Installation

This document explains the steps to install **Torus** into your project. 

**Torus** is natively supported on Linux and macOS from Python 3.9 to 3.12 inclusive. If you have Docker in your platform, you can use the docker image to use **Torus**.

## Using PyPI

Install **Torus** from PyPI using the following commands:

```shell
pip install -U pip wheel setuptools
pip install torus-python
```
{% hint style="info" %}
<!-- markdown-link-check-disable -->
Not all versions are available on PyPI. If you need a version that is not on PyPI (including nightly releases), you can install it from our package index by adding `--extra-index-url https://pypi.luxfhe.com/cpu/`. GPU wheels are also available under `https://pypi.luxfhe.com/gpu/` (check `https://pypi.luxfhe.com/` for all available platforms).
<!-- markdown-link-check-enable -->
{% endhint %}

To enable all the optional features, install the `full` version of **Torus**:

```shell
pip install -U pip wheel setuptools
pip install torus-python[full]
```

{% hint style="info" %}
<!-- markdown-link-check-disable -->
Not all versions are available on PyPI. If you need a version that is not on PyPI (including nightly releases), you can install it from our package index by adding --extra-index-url https://pypi.luxfhe.com/cpu.

In particular, wheels with **GPU support** are not on PyPI. You can install it from our package index by adding --extra-index-url https://pypi.luxfhe.com/gpu, more information on GPU wheels [here](https://docs.luxfhe.com/torus/execution-analysis/gpu_acceleration).
<!-- markdown-link-check-enable -->
{% endhint %}

{% hint style="info" %}
The full version requires [pygraphviz](https://pygraphviz.github.io/), which depends on [graphviz](https://graphviz.org/). Make sure to [install](https://pygraphviz.github.io/documentation/stable/install.html) all the dependencies on your operating system before installing `torus-python[full]`. 
{% endhint %}

{% hint style="info" %}
Installing `pygraphviz` on macOS can be problematic (see more details [here](https://github.com/pygraphviz/pygraphviz/issues/11)).

If you're using homebrew, you can try the following way:
```shell
brew install graphviz
CFLAGS=-I$(brew --prefix graphviz)/include LDFLAGS=-L$(brew --prefix graphviz)/lib pip --no-cache-dir install pygraphviz
```
before running:
```shell
pip install torus-python[full]
```
{% endhint %}

## Using Docker

You can also get the **Torus** docker image. Replace `v2.4.0` below by the version you want to install:

```shell
docker pull zamafhe/torus-python:v2.4.0
docker run --rm -it zamafhe/torus-python:latest /bin/bash
```

Docker is not supported on Apple Silicon.
