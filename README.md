# Torus

**The Lux Industries FHE compiler.** Write Python or MLIR; compile to encrypted execution on CPU, GPU (CUDA / Metal / WebGPU), and (planned) FPGA — all from one source.

[![License](https://img.shields.io/badge/License-BSD--3--Clause--Clear-blue.svg)](LICENSE.txt)

---

## What Torus is for

- **On-chain encrypted computation.** Write a Python function with encrypted inputs; Torus emits a circuit that the Lux FHE precompile (`lux/precompile/fhe` at addresses `0x...80`–`0x...83`) or the Lux FHE coprocessor (`lux/fhe-coprocessor`) can evaluate.
- **Private machine learning.** [`luxfhe/ml-sdk`](https://github.com/luxfhe/ml-sdk) (TorusML) lifts scikit-learn, PyTorch, and ONNX models to FHE circuits via Torus.
- **Hardware acceleration.** Codegen targets the [`luxcpp/gpu`](https://github.com/luxfi/luxcpp) gen-1 dispatcher, which routes to `lux-private/gpu-kernels` for production GPU performance and `lux-private/fpga` for FPGA tape execution.

## Quick start

```python
from torus import fhe

@fhe.compiler({"x": "encrypted"})
def add(x):
    return x + 5

circuit = add.compile(inputset=range(10))
result = circuit.encrypt_run_decrypt(7)
# 12
```

## Architecture

```
   Python / MLIR source
            │
            ▼
   torus.fhe (frontend)        ← write circuits in Python / MLIR
            │
            ▼
   Torus dialect (HIR)         ← typed-integer, noise-tracked, bootstrap-implicit
            │
            ▼
   MIR (gate / poly level)     ← bit-decomposed (TFHE) or polynomial (CKKS/BGV/BFV)
            │
            ▼
   LIR per backend
            │
   ┌────────┼─────────┬─────────────┐
   ▼        ▼         ▼             ▼
  CPU     CUDA      Metal         FPGA
(always (luxcpp/   (luxcpp/    (bytecode
on,     gpu vtbl   gpu vtbl    tape over
BSD-3   →           →           pinned-ISA
Eco)   lux-private lux-private bitstream;
       /gpu-       /gpu-       lux-private
       kernels/    kernels/    /fpga)
       cuda)       metal)
                 + WebGPU (luxcpp/gpu → lux-private/gpu-kernels/wgsl)
```

The Torus dialect is a single source of truth; per-backend lowering is a thin codegen pass over the gen-1 vtbl C ABI at `luxcpp/gpu/include/lux/gpu/backend_plugin.h` (~80 slots covering NTT, FHE PBS / keyswitch / blind-rotate, BLS / BN254 / KZG, ML-DSA / ML-KEM / SLH-DSA, FROST / CGGMP21 / Ringtail). Backends register at `dlopen` time; CPU fallback is always linked in.

## Repository layout

| Path | Purpose |
|---|---|
| `frontends/torus-python/torus/` | Python frontend (`torus.fhe`, `torus.fhe.compilation`, `torus.fhe.mlir`) |
| `frontends/torus-rust/` | Rust frontend + key-management + macro library |
| `compilers/torus-compiler/` | MLIR-based Torus compiler (the dialect + lowering passes + LLVM tail) |
| `compilers/torus-optimizer/` | Crypto-parameter optimizer (selects NTT-friendly primes, ring degrees, noise budgets) |
| `backends/torus-cpu/` | CPU runtime (Rust); always-on baseline |
| `backends/torus-cuda/` | CUDA runtime (seeds the Phase 3 `lux-private/gpu-kernels` integration) |
| `tools/torus-protocol/` | Wire-format protocol buffers / message framing |
| `tools/parameter-curves/` | Security-level parameter tables for ring-LWE, M-LWE, RLWE |

## Schemes supported

Torus compiles to any FHE scheme exposed by the Lux primitive stack:

- **TFHE / CGGI** (boolean gates, PBS) — via [`luxfi/fhe`](https://github.com/luxfi/fhe) (Go) on [`luxfi/lattice`](https://github.com/luxfi/lattice) (RLWE/RGSW)
- **CKKS** (approximate arithmetic — ML, signal processing) — via [`luxfi/lattice/schemes/ckks`](https://github.com/luxfi/lattice)
- **BFV / BGV** (exact integer arithmetic) — via [`luxfi/lattice/schemes/{bfv,bgv}`](https://github.com/luxfi/lattice)
- **Multiparty / threshold** — via [`luxfi/lattice/multiparty/{mpckks,mpbgv}`](https://github.com/luxfi/lattice) + [`luxfi/fhe/pkg/threshold`](https://github.com/luxfi/fhe) (M-of-N Shamir-over-$\mathbb{Z}_q$)

## License

BSD 3-Clause Clear. See [`LICENSE.txt`](LICENSE.txt) and [`NOTICE`](NOTICE).

The original work is © 2024 ZAMA, used under license. Modifications are © 2026 Lux Industries Inc. Per BSD-3-Clause-Clear §3, no name of ZAMA or its contributors is used to endorse Torus — this is a Lux Industries product, branded as such everywhere it is marketed. The attribution in `NOTICE` is legal compliance, not endorsement.

## The Lux FHE family

| Product | What it is | Repo |
|---|---|---|
| **Lux FHE** | Umbrella framework | — |
| **Torus** | FHE compiler / runtime (this repo) | `luxfhe/torus` |
| **TorusVM** | Core FHE runtime VM (what Torus compiles to) | (embedded in Torus) |
| **TorusEVM** | Encrypted EVM execution | [`luxfhe/fhevm`](https://github.com/luxfhe/fhevm) (Lux FHEVM stack) |
| **TorusML** | Private machine learning | [`luxfhe/ml-sdk`](https://github.com/luxfhe/ml-sdk) |
| **TorusNet** | Threshold decryption network | [`luxfhe/threshold`](https://github.com/luxfhe/threshold) |
| Lux-FHE (Go library) | TFHE on `luxfi/lattice` | [`luxfi/fhe`](https://github.com/luxfi/fhe) |
| Lux-Lattice (Go library) | CKKS / BGV / BFV / RLWE / RGSW | [`luxfi/lattice`](https://github.com/luxfi/lattice) |

## Status

This is the **Phase 2A initial fork**. It contains the renamed source tree from the upstream compiler; downstream PyPI publication, CI wiring, full integration test passes, and the production CKKS GPU kernel port (Phase 3) are tracked in follow-up issues.

## Contributing

Issues + PRs welcome at [`github.com/luxfhe/torus`](https://github.com/luxfhe/torus). Run `make test` for the local conformance suite (CPU backend always works; GPU backend requires a `lux-license` token with the `gpu` scope per the `lux-private/gpu-kernels` distribution policy).
