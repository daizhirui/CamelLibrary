# Soft Float Library for M2  {#soft_fp}

To use this library, please include `soft_fp.h`.

## Interface

```C
float fp_float32_neg(float a_fp);

float fp_float32_abs(float a_fp);

float fp_float32_add(float a_fp, float b_fp);

float fp_float32_sub(float a_fp, float b_fp);

float fp_float32_mult(float a_fp, float b_fp);

float fp_float32_div(float a_fp, float b_fp);

long fp_float32_to_int32(float a_fp);

float fp_int32_to_float32(long af);

float fp_uint32_to_float32(unsigned long af);

double fp_float32_to_float64(float a_fp);

float fp_float64_to_float32(double a_dfp);

int fp_float32_cmp(float a_fp, float b_fp);

float fp_float32_sqrt(float a);

float fp_float32_cos(float rad);

float fp_float32_sin(float rad);

float fp_float32_atan(float x);

float fp_float32_atan2(float y, float x);

float fp_float32_exp(float x);

float fp_float32_log(float x);

float fp_float32_pow(float x, float y);

```

## Example

```C
float a = fp_int32_to_float32（-123）；  // convert int -123 -> float type
float b = fp_uint32_to_float32(2345);   // convert unsigned int 2345 -> float type
float c = fp_float32_add(a, b);         // floating point add
float d = fp_float32_sqr(b);            // floating point sqrt
```
