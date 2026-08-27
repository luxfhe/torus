<!-- markdownlint-disable -->

<a href="../../frontends/torus-python/torus/fhe/compilation/value.py#L0"><img align="right" style="float:right;" src="https://img.shields.io/badge/-source-cccccc?style=flat-square"></a>

# <kbd>module</kbd> `torus.fhe.compilation.value`
Declaration of `Value` class. 



---

<a href="../../frontends/torus-python/torus/fhe/compilation/value.py#L10"><img align="right" style="float:right;" src="https://img.shields.io/badge/-source-cccccc?style=flat-square"></a>

## <kbd>class</kbd> `Value`
A public value object that can be sent between client and server. 

<a href="../../frontends/torus-python/torus/fhe/compilation/value.py#L17"><img align="right" style="float:right;" src="https://img.shields.io/badge/-source-cccccc?style=flat-square"></a>

### <kbd>method</kbd> `__init__`

```python
__init__(inner: TransportValue)
```








---

<a href="../../frontends/torus-python/torus/fhe/compilation/value.py#L20"><img align="right" style="float:right;" src="https://img.shields.io/badge/-source-cccccc?style=flat-square"></a>

### <kbd>method</kbd> `deserialize`

```python
deserialize(buffer: bytes) → Value
```

Deserialize a Value from bytes. 

---

<a href="../../frontends/torus-python/torus/fhe/compilation/value.py#L27"><img align="right" style="float:right;" src="https://img.shields.io/badge/-source-cccccc?style=flat-square"></a>

### <kbd>method</kbd> `serialize`

```python
serialize() → bytes
```

Serialize a Value to bytes. 


