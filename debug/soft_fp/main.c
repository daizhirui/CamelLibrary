//
// Created by 戴植锐 on 2018/6/1.
//
#include "soft_fp.h"
int main()
{
    double double1 = 3.141592653;
    float float1 = 3.141592653;

    double double2 = fp_float32_to_float64(float1);
    float float2 = fp_float64_to_float32(double1);
}