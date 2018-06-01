/*--------------------------------------------------------------------
 * TITLE: M2 Floating Point Library
 * AUTHOR: John, Hongyan Zhao, Zhirui Dai
 * DATE CREATED:
 * FILENAME: math.c
 * PROJECT: M2 CPU core
 * COPYRIGHT: Software placed into the public domain by the author.
 *    Software 'as is' without warranty.  Author liable for nothing.
 * DESCRIPTION:
 *    M2 Floating Point Library
 *--------------------------------------------------------------------
 * IEEE_fp = sign(1) | exponent(8) | fraction(23)
 * 1 << 23 | fraction part = BINARY_FLOAT
 * cos(x)=1-x^2/2!+x^4/4!-x^6/6!+...
 * exp(x)=1+x+x^2/2!+x^3/3!+...
 * ln(1+x)=x-x^2/2+x^3/3-x^4/4+...
 * atan(x)=x-x^3/3+x^5/5-x^7/7+...
 * pow(x,y)=exp(y*ln(x))
 * x=tan(a+b)=(tan(a)+tan(b))/(1-tan(a)*tan(b))
 * atan(x)=b+atan((x-atan(b))/(1+x*atan(b)))
 * ln(a*x)=ln(a)+ln(x); ln(x^n)=n*ln(x)
 *--------------------------------------------------------------------*/

#include "math.h"
#include <stdio.h>

/**
 * @brief Convert the memory space from unsigned long to float.
 */
#define FtoL(X) (*(unsigned long*)&(X))

/**
 * @brief Convert the memory space from float to unsigned long.
 */
#define LtoF(X) (*(float*)&(X))

unsigned long a, b, c;      // unsigned long expression of a_fp and b_fp.
unsigned long as, bs, cs;   // sign
unsigned long af, bf, cf;   // fraction
long ae, be, ce;            // exponent
unsigned long a2, a1, b2, b1, med1, med2;
unsigned long hi, lo;       // high 32 bits and low 32 bits
long d;

#define hiOfDF(X)   ((unsigned long*)&(X))[1]
#define loOfDF(X)   ((unsigned long*)&(X))[0]
#define DFtoL(X)    (*(unsigned long*)&(X))
#define LtoDF(X)    (*(double*)&(X))

/**
 * @brief Calculate the negative value of a_fp.
 * @param a_fp The value to calculate.
 * @return The negative value of a_fp.
 */
float FP_Neg(float a_fp)
{
    unsigned long a;
    a = FtoL(a_fp);
    a ^= 0x80000000;
    return LtoF(a);
}

float FP_Abs(float a_fp)
{
    if (a_fp<0) {
        return -a_fp;
    } else {
        return a_fp;
    }
}

/**
 * @brief Add arithmetic operation.
 * @param a_fp Number 1 to add.
 * @param b_fp Number 2 to add.
 * @return The sum of a_fp and b_fp.
 */
float FP_Add(float a_fp, float b_fp)
{
    unsigned long a, b, c;          // unsigned long expression of a_fp and b_fp.
    unsigned long as, bs, cs;       // sign
    long ae, af, be, bf, ce, cf;    // exponent and fraction
    a = FtoL(a_fp);
    b = FtoL(b_fp);
    as = a >> 31;                        //sign
    ae = (a >> 23) & 0xff;               //exponent
    af = 0x00800000 | (a & 0x007fffff);  //fraction
    bs = b >> 31;
    be = (b >> 23) & 0xff;
    bf = 0x00800000 | (b & 0x007fffff);
    if(ae > be)                     // align the fraction according to the exponent
    {
        if(ae - be < 24)            // exponent difference bigger than 24 result in precision lost
            bf >>= ae - be;
        else
            bf = 0;
        ce = ae;
    }
    else
    {
        if(be - ae < 24)
            af >>= be - ae;
        else
            af = 0;
        ce = be;
    }
    cf = (as ? -af : af) + (bs ? -bf : bf); // calculate the fraction of the sum.
    cs = cf < 0;
    cf = cf>=0 ? cf : -cf;
    if(cf == 0)
        return LtoF(cf);
    while(cf & 0xff000000)                  // correct the mantissa, 24 bits at most
    {
        ++ce;
        cf >>= 1;
    }
    while((cf & 0xff800000) == 0)           // Bit23 must be 1.
    {
        --ce;
        cf <<= 1;
    }
    c = (cs << 31) | (ce << 23) | (cf & 0x007fffff);
    if(ce < 1)
        c = 0;
    return LtoF(c);
}

/**
 * @brief Subtraction arithmetic operation.
 * @param a_fp The minuend.
 * @param b_fp The subtrahend.
 * @return The result.
 */
float FP_Sub(float a_fp, float b_fp)
{
    return FP_Add(a_fp, FP_Neg(b_fp));
}

/**
 * @brief Multiplication.
 * @param a_fp The number 1 to multiply.
 * @param b_fp The number 2 to multiply.
 * @return The product.
 */
float FP_Mult(float a_fp, float b_fp)
{
    // unsigned long a, b, c;      // unsigned long expression of a_fp and b_fp.
    // unsigned long as, bs, cs;   // sign
    // unsigned long af, bf, cf;   // fraction
    // long ae, be, ce;            // exponent
    // unsigned long a2, a1, b2, b1, med1, med2;
    // unsigned long hi, lo;       // high 32 bits and low 32 bits
    // conversion
    a = FtoL(a_fp);
    b = FtoL(b_fp);
    as = a >> 31;
    ae = (a >> 23) & 0xff;
    af = 0x00800000 | (a & 0x007fffff);
    bs = b >> 31;
    be = (b >> 23) & 0xff;
    bf = 0x00800000 | (b & 0x007fffff);
    // calculation
    cs = as ^ bs;                               // calculate sign
    a1 = af & 0xffff;                           // low 16 bits of af
    a2 = af >> 16;                              // high 16 bits of bf
    b1 = bf & 0xffff;                           // low 16 bits of af
    b2 = bf >> 16;                              // high 16 bits of bf
    lo = a1 * b1;                               // low part, starts from bit0
    med1 = a2 * b1 + (lo >> 16);                // cross part1, starts from bit16
    med2 = a1 * b2;                             // cross part2, starts from bit16
    hi = a2 * b2 + (med1 >> 16) + (med2 >> 16); // high part, starts from bit32
    med1 = (med1 & 0xffff) + (med2 & 0xffff);   // calculate carry-over
    hi += (med1 >> 16);                         // add carry-over, high part calculated
    lo = (med1 << 16) | (lo & 0xffff);          // low part calculated
    cf = (hi << 9) | (lo >> 23);                // fraction calculated
    /** Actual fraction in calculation has 24 bits, and hi uses 16 bits at most.
     * What's more, bit15 is the exceeding bit, so it should be moved to bit24.
     */
    ce = ae + be - 0x80 + 1;                    // exponent calculated
    if(cf == 0)
        return LtoF(cf);
    while(cf & 0xff000000)
    {
        ++ce;
        cf >>= 1;
    }
    c = (cs << 31) | (ce << 23) | (cf & 0x007fffff);
    if(ce < 1)
        c = 0;
    return LtoF(c);
}

/**
 * @brief Float Division.
 *
 * @param a_fp Dividend.
 * @param b_fp Divisor.
 * @return float Quotient.
 */
float FP_Div(float a_fp, float b_fp)
{
    // unsigned long a, b, c;
    // unsigned long as, af, bs, bf, cs, cf;
    // unsigned long a1, b1;
    // unsigned long a2, b2, med1, med2;
    // unsigned long hi, lo;
    // long ae, be, ce, d;
    a = FtoL(a_fp);
    b = FtoL(b_fp);
    as = a >> 31;
    ae = (a >> 23) & 0xff;
    af = 0x00800000 | (a & 0x007fffff);
    bs = b >> 31;
    be = (b >> 23) & 0xff;
    bf = 0x00800000 | (b & 0x007fffff);
    cs = as ^ bs;                               // calculate sign
    ce = ae - (be - 0x80) + 6 - 8;
    a1 = af << 4; //8                           // magnify
    b1 = bf >> 8;                               // ignore low 8-bit, it doesn't influence precision
    cf = a1 / b1;                               // calculate the quotient
    cf <<= 12; //8                              // rescale to 24 bits
    // calculate the remainder
    a1 = cf & 0xffff;
    a2 = cf >> 16;
    b1 = bf & 0xffff;
    b2 = bf >> 16;
    lo = a1 * b1;
    med1 =a2 * b1 + (lo >> 16);
    med2 = a1 * b2;
    hi = a2 * b2 + (med1 >> 16) + (med2 >> 16);
    med1 = (med1 & 0xffff) + (med2 & 0xffff);
    hi += (med1 >> 16);
    lo = (med1 << 16) | (lo & 0xffff);

    lo = (hi << 8) | (lo >> 24);
    d = af - lo;                                //remainder
    assert(-0xffff < d && d < 0xffff);
    // correction
    d <<= 16;
    b1 = bf >> 8;
    d = d / (long)b1;
    cf += d;

    if(cf == 0)
        return LtoF(cf);
    while(cf & 0xff000000)
    {
        ++ce;
        cf >>= 1;
    }
    if(ce < 0)
        ce = 0;
    c = (cs << 31) | (ce << 23) | (cf & 0x007fffff);
    if(ce < 1)
        c = 0;
    return LtoF(c);
}

/**
 * @brief Convert float to signed long.
 *
 * @param a_fp float to be converted to long.
 * @return long the long integer.
 */
long FP_ToLong(float a_fp)
{
    unsigned long a;
    unsigned long as;
    long ae;
    long af, shift;
    a = FtoL(a_fp);
    as = a >> 31;
    ae = (a >> 23) & 0xff;
    af = 0x00800000 | (a & 0x007fffff);
    af <<= 7;
    shift = -(ae - 0x80 - 29);
    if(shift > 0)
    {
        if(shift < 31)
            af >>= shift;
        else
            af = 0;
    }
    af = as ? -af: af;
    return af;
}

/**
 * @brief Convert signed long to float.
 *
 * @param af long value to be converted to float.
 * @return float the float.
 */
float FP_ToFloat(long af)
{
    unsigned long a;
    unsigned long as, ae;
    as = af>=0 ? 0: 1;
    af = af>=0 ? af: -af;
    ae = 0x80 + 22;
    if(af == 0)
        return LtoF(af);
    while(af & 0xff000000)
    {
        ++ae;
        af >>= 1;
    }
    while((af & 0xff800000) == 0)
    {
        --ae;
        af <<= 1;
    }
    a = (as << 31) | (ae << 23) | (af & 0x007fffff);
    return LtoF(a);
}

/**
 * @brief Convert unsigned long to float.
 *
 * @param af unsigned long value to be converted to float.
 * @return float the float.
 */
float FP_UnsignedLongToFloat(unsigned long af)
{
    unsigned long a;
    unsigned long as = 0;
    unsigned long ae = 0x80 + 22;
    if(af == 0)
        return LtoF(af);
    while(af & 0xff000000)
    {
        ++ae;
        af >>= 1;
    }
    while((af & 0xff800000) == 0)
    {
        --ae;
        af <<= 1;
    }
    a = (as << 31) | (ae << 23) | (af & 0x007fffff);
    return LtoF(a);
}

//0 iff a==b; 1 iff a>b; -1 iff a<b
/**
 * @brief Compare two float value.
 *
 * @param a_fp float value a.
 * @param b_fp float value b.
 * @return int  0 if a==b; 1 if a>b; -1 if a<b;
 */
int FP_Cmp(float a_fp, float b_fp)
{
    unsigned long a, b;
    unsigned long as, ae, af, bs, be, bf;
    int gt;
    a = FtoL(a_fp);
    b = FtoL(b_fp);
    //      puts("cmp: a="); print_hex(a); puts(" b="); print_hex(b);
    if(a == b)
        return 0;
    as = a >> 31;
    bs = b >> 31;
    if(as > bs)
        return -1;
    if(as < bs)
        return 1;
    gt = as ? -1 : 1;
    ae = (a >> 23) & 0xff;
    be = (b >> 23) & 0xff;
    if(ae > be)
        return gt;
    if(ae < be)
        return -gt;
    af = 0x00800000 | (a & 0x007fffff);
    bf = 0x00800000 | (b & 0x007fffff);
    if(af > bf)
        return gt;
    return -gt;
}

int __ltsf2(float a, float b)
{
    return FP_Cmp(a, b);
}

int __lesf2(float a, float b)
{
    return FP_Cmp(a, b);
}

int __gtsf2(float a, float b)
{
    return FP_Cmp(a, b);
}

int __gesf2(float a, float b)
{
    return FP_Cmp(a, b);
}

int __eqsf2(float a, float b)
{
    return FtoL(a) != FtoL(b);
}

int __nesf2(float a, float b)
{
    return FtoL(a) != FtoL(b);
}

/**
 * @brief Returns the square root of x.
 *
 * @param x Value whose square root is computed.
 * @return float Square root of x.If x < 0, return 0.
 */
float FP_Sqrt(float x)
{
    float x1, y1, x2, y2, x3;
    long i;
    if (x < 0)  return 0;
    x1 = FP_ToFloat(1);
    y1 = FP_Sub(FP_Mult(x1, x1), x);  //y1=x1*x1-a;
    x2 = FP_ToFloat(100);
    y2 = FP_Sub(FP_Mult(x2, x2), x);
    for(i = 0; i < 10; ++i)
    {
        if(FtoL(y1) == FtoL(y2))
            return x2;
        //x3=x2-(x1-x2)*y2/(y1-y2);
        x3 = FP_Sub(x2, FP_Div(FP_Mult(FP_Sub(x1, x2), y2), FP_Sub(y1, y2)));
        x1 = x2;
        y1 = y2;
        x2 = x3;
        y2 = FP_Sub(FP_Mult(x2, x2), x);
    }
    return x2;
}


//   static const float fcos0 = 2.33;
/**
 * @brief Returns the cosine of an angle of x radians.
 *
 * @param rad Value representing an angle expressed in radians.
 * @return float Cosine of x radians.
 */
float FP_Cos(float rad)
{
    // long a1, b1;
    // float ra1;

    int n;
    float answer, x2, top, bottom, sign;
    while(FP_Cmp(rad, PI2) > 0) {
        rad = FP_Sub(rad, PI2);
    }
    while(FP_Cmp(rad, (float)0.0) < 0) {
        rad = FP_Add(rad, PI2);
    }

    answer = FP_ToFloat(1);
    sign = FP_ToFloat(1);

    if(FP_Cmp(rad, PI) >= 0)
    {
        rad = FP_Sub(rad, PI);
        sign = FP_ToFloat(-1);
    }
    if(FP_Cmp(rad, PI_2) >= 0)
    {
        rad = FP_Sub(PI, rad);
        sign = FP_Neg(sign);
    }
    x2 = FP_Mult(rad, rad);
    top = FP_ToFloat(1);
    bottom = FP_ToFloat(1);
    for(n = 2; n < 12; n += 2)
    {
        top = FP_Mult(top, FP_Neg(x2));
        bottom = FP_Mult(bottom, FP_ToFloat((n - 1) * n));
        answer = FP_Add(answer, FP_Div(top, bottom));
    }
    return FP_Mult(answer, sign);
}

/**
 * @brief Returns the sine of an angle of x radians.
 *
 * @param rad Value representing an angle expressed in radians.
 * @return float Sine of x radians.
 */
float FP_Sin(float rad)
{
    return FP_Cos(FP_Sub(rad, PI_2));
}

/**
 * @brief Returns the principal value of the arc tangent of x, expressed in radians.
 *
 * @param x Value whose arc tangent is computed.
 * @return float Principal arc tangent of x, in the interval [-pi/2,+pi/2] radians.One radian is equivalent to 180/PI degrees.
 */
float FP_Atan(float x)
{
    //float b = FP_Div(PI, FP_ToFloat(800000000));
    //float atan_b = FP_Div(FP_ToFloat(37419668), FP_ToFloat(100000000));

    int n;
    float answer, x2, top;
    if(FP_Cmp(x, FP_ToFloat(0)) >= 0)
    {
        if(FP_Cmp(x, FP_ToFloat(1)) > 0)
            return FP_Sub(PI_2, FP_Atan(FP_Div(FP_ToFloat(1), x)));
    }
    else
    {
        if(FP_Cmp(x, FP_ToFloat(-1)) > 0)
            return FP_Sub(-PI_2, FP_Atan(FP_Div(FP_ToFloat(1), x)));
    }
    if(FP_Cmp(x, FP_Div(FP_ToFloat(45), FP_ToFloat(100))) > 0)
    {
        answer = FP_Div(FP_Sub(x, ATAN_PI_8), FP_Add(FP_ToFloat(1), FP_Mult(x, ATAN_PI_8)));
        answer = FP_Sub(FP_Add(PI_8, FP_Atan(answer)), FP_Div(FP_ToFloat(34633), FP_ToFloat(1000000)));
        return answer;
    }
    if(FP_Cmp(x, FP_Div(FP_ToFloat(-45), FP_ToFloat(100))) < 0)
    {
        x = FP_Neg(x);
        answer = FP_Div(FP_Sub(x, ATAN_PI_8), FP_Add(FP_ToFloat(1), FP_Mult(x, ATAN_PI_8)));
        answer = FP_Sub(FP_Add(PI_8, FP_Atan(answer)), FP_Div(FP_ToFloat(34633), FP_ToFloat(1000000)));
        return FP_Neg(answer);
    }
    answer = x;
    x2 = FP_Mult(FP_Neg(x), x);
    top = x;
    for(n = 3; n < 14; n += 2)
    {
        top = FP_Mult(top, x2);
        answer = FP_Add(answer, FP_Div(top, FP_ToFloat(n)));
    }
    return answer;
}

/**
 * @brief Returns the principal value of the arc tangent of y/x, expressed in radians.
 *
 * @param y Value representing the proportion of the y-coordinate.
 * @param x Value representing the proportion of the x-coordinate.
 * @return float Principal arc tangent of y/x, in the interval [-pi,+pi] radians.
                One radian is equivalent to 180/PI degrees.
                If x is zero, return 0.
 */
float FP_Atan2(float y, float x)
{
    float answer,r;
    if ( x == 0 ) return 0;
    r = y / x;
    answer = FP_Atan(r);
    if(FP_Cmp(x, FP_ToFloat(0)) < 0)
    {
        if(FP_Cmp(y, FP_ToFloat(0)) > 0)
            answer = FP_Add(answer, PI);
        else
            answer = FP_Sub(answer, PI);
    }
    return answer;
}

/**
 * @brief Returns the base-e exponential function of x, which is e raised to the power x.
 *
 * @param x   Value of the exponent.
 * @return float  Exponential value of x.
 */
float FP_Exp(float x)
{
    //float e2     = FP_Div(FP_ToFloat(738905609), FP_ToFloat(100000000));
    //float inv_e2 = FP_Div(FP_ToFloat(13533528), FP_ToFloat(100000000));
    float answer, top, bottom, mult;
    int n;

    mult = FP_ToFloat(1);
    while(FP_Cmp(x, FP_ToFloat(2)) > 0)
    {
        mult = FP_Mult(mult, E2);
        x = FP_Add(x, FP_ToFloat(-2));
    }
    while(FP_Cmp(x, FP_ToFloat(-2)) < 0)
    {
        mult = FP_Mult(mult, INV_E2);
        x = FP_Add(x, FP_ToFloat(2));
    }
    answer = FP_Add(FP_ToFloat(1), x);
    top = x;
    bottom = FP_ToFloat(1);
    for(n = 2; n < 15; ++n)
    {
        top = FP_Mult(top, x);
        bottom = FP_Mult(bottom, FP_ToFloat(n));
        answer = FP_Add(answer, FP_Div(top, bottom));
    }
    return FP_Mult(answer, mult);
}

/**
 * @brief The natural logarithm is the base-e logarithm: the inverse of the natural exponential function (FP_Exp).
 *
 * @param x  Value whose logarithm is calculated.
 * @return float Natural logarithm of x. If x <= 0, return 0.
 */
float FP_Log(float x)
{
    //float log_2       = FP_Div(FP_ToFloat(69314718), FP_ToFloat(100000000)); //LN_2
    //float num_1p5     = FP_Div(FP_ToFloat(15), FP_ToFloat(10));      // 1.5
    //float num_0p5     = FP_Div(FP_ToFloat(5), FP_ToFloat(10));       // 0.5
    //float num_0p0625  = FP_Div(FP_ToFloat(625), FP_ToFloat(10000));  // 0.0625

    int n;
    float answer, top, add;
    if (x <= 0)  return 0;     // the value is negative, error!
    add = FP_ToFloat(0);
    while(FP_Cmp(x, FP_ToFloat(16)) > 0)
    {
        x = FP_Mult(x, 0.0625);
        add = FP_Add(add, FP_Mult(LN_2, FP_ToFloat(4)));
    }
    while(FP_Cmp(x, 1.5) > 0)
    {
        x = FP_Mult(x, 0.5);
        add = FP_Add(add, LN_2);
    }
    while(FP_Cmp(x, 0.5) < 0)
    {
        x = FP_Mult(x, FP_ToFloat(2));
        add = FP_Sub(add, LN_2);
    }
    x = FP_Sub(x, FP_ToFloat(1));
    answer = FP_ToFloat(0);
    top = FP_ToFloat(-1);
    for(n = 1; n < 14; ++n)
    {
        top = FP_Mult(top, FP_Neg(x));
        answer = FP_Add(answer, FP_Div(top, FP_ToFloat(n)));
    }
    return FP_Add(answer, add);
}

/**
 * @brief Compute power.
 *
 * @param x  Base value.
 * @param y  Exponent value.
 * @return float  The result of raising base to the power exponent.
 */
float FP_Pow(float x, float y)
{
    return FP_Exp(y * FP_Log(x));
}

/********************************************/
//These five functions will only be used if the flag "-mno-mul" is enabled
#ifdef USE_SW_MULT
unsigned long __mulsi3(unsigned long a, unsigned long b)
{
    unsigned long answer = 0;
    while(b)
    {
        if(b & 1)
            answer += a;
        a <<= 1;
        b >>= 1;
    }
    return answer;
}


static unsigned long DivideMod(unsigned long a, unsigned long b, int doMod)
{
    unsigned long upper=a, lower=0;
    int i;
    a = b << 31;
    for(i = 0; i < 32; ++i)
    {
        lower = lower << 1;
        if(upper >= a && a && b < 2)
        {
            upper = upper - a;
            lower |= 1;
        }
        a = ((b&2) << 30) | (a >> 1);
        b = b >> 1;
    }
    if(!doMod)
        return lower;
    return upper;
}


unsigned long __udivsi3(unsigned long a, unsigned long b)
{
    return DivideMod(a, b, 0);
}


long __divsi3(long a, long b)
{
    long answer, negate=0;
    if(a < 0)
    {
        a = -a;
        negate = !negate;
    }
    if(b < 0)
    {
        b = -b;
        negate = !negate;
    }
    answer = DivideMod(a, b, 0);
    if(negate)
        answer = -answer;
    return answer;
}


unsigned long __umodsi3(unsigned long a, unsigned long b)
{
    return DivideMod(a, b, 1);
}
#endif
