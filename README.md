# Arbitrary-sized floating-point conversion routine


## TODO
* algorithm for >64b floats
* fast type in template
* report loss of precission

## Reference of existing floating point types

Title | Width | Mantissa | Exponent | Short | Remarks
-|-|-|-|-|-
[Minifloat](https://en.wikipedia.org/wiki/Minifloat) | 8 | 3 | 4 | mini |
[FP16](https://en.wikipedia.org/wiki/Half-precision_floating-point_format) | 16 | 10 | 5 | half |
[bfloat16](https://en.wikipedia.org/wiki/Bfloat16_floating-point_format) | 16 | 7 | 8 | bfloat16 | AI, AVX-512 BF16, TensorFlow, ...
NV TensorFloat | 19 | 10 | 8 | - | NVidia's TensorFloat
AMD fp24 | 24 | 16 | 7 | - | 
PXR24 | 24 | 15 | 8 | - | Pixar
[IEEE 754 single](https://en.wikipedia.org/wiki/Single-precision_floating-point_format) | 32 | 23 | 8 | float |
[IEEE 754 double](https://en.wikipedia.org/wiki/Double-precision_floating-point_format) | 64 | 52 | 11 | double |
[IEEE 754 extended](https://en.wikipedia.org/wiki/Extended_precision) | 80 | 64 | 15 | long double |

*When calling this library, template parameters refer to **Width** and **Exponent** fields in this table.*