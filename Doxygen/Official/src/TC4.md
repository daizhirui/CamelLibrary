# TC4 Library for M2  {#TC4}

## Interface

```C
void RT_TC4_AllPWM_On();

void RT_TC4_AllPWM_Off();

void RT_TC4_PWM_On(n);

void RT_TC4_PWM_Off(n);

void RT_TC4_SetAllPWM(pw0_en, div0, ref0, pwm1_en, div1, ref1);

void RT_TC4_SetPWM(n, pwm_en, div, ref);
```

## Example

```C
RT_TC4_AllPWM_On();          // turn on TC4 pwm0 and pwm1
RT_TC4_SetPWM(0, ON, 2, 4);  // set pwm0, div=2, ref=4
```
