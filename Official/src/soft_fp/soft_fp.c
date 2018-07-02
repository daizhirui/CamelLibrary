/**
 * @file soft_fp.c
 * @author Zhirui Dai
 * @date 1 Jun 2018
 * @copyright 2018 Zhirui
 * @brief Soft float library
 */

#include "soft_fp.h"

/*! \cond PRIVATE */
#define __float32_to_uint32__(X)    (*(unsigned long*)&(X))
#define __uint32_to_float32__(X)    (*(float*)&(X))
#define __high32_of_float64__(X)    (((unsigned long*)&X)[1])
#define __low32_of_float64__(X)     (((unsigned long*)&X)[0])
#define __uint32x2_to_float64__(X)  (*(unsigned long*)&(X))
// float32
#define FLOAT32_SIGN_POS            31
#define FLOAT32_EXPO_POS            23
#define FLOAT32_EXPO_BASE           0x80        // 0x80 - 1
#define FLOAT32_EXPO_MASK           0xff
#define FLOAT32_FRAC_MASK           0x007fffff
#define FLOAT32_FRAC_LENGTH         23
#define FLOAT32_REIGHT_SHIFT_MASK   0xff000000
#define FLOAT32_LEFT_SHIFT_MASK     0xff800000
#define __float32_sign__(X)         (X>>FLOAT32_SIGN_POS)
#define __float32_expo__(X)         ((X>>FLOAT32_EXPO_POS)&FLOAT32_EXPO_MASK)
#define __float32_frac__(X)         (0x00800000 | (X&FLOAT32_FRAC_MASK))
#define __assemble_float32__(S,E,F) ((S << FLOAT32_SIGN_POS) | ((E) << FLOAT32_EXPO_POS) | ((F) & FLOAT32_FRAC_MASK))
unsigned long __NAN__ = 0x7f800000;
#define FLOAT32_NaN()               (*(float*)&(__NAN__))
// float64
#define FLOAT64_SIGN_POS                    63
#define FLOAT64_EXPO_POS                    52
#define FLOAT64_EXPO_HI_POS                 20
#define FLOAT64_EXPO_BASE                   0x400   // 0x400 - 1
#define FLOAT64_EXPO_MASK                   0x7FF
#define __float64_lo(X)                     (((unsigned long*)(&X))[0])
#define __float64_hi(X)                     (((unsigned long*)(&X))[1])
// float32 to float64
#define FLOAT32_TO64_FRAC_LO_MASK           0x7
#define FLOAT32_TO64_FRAC_HI_MASK           0x7FFFF8
#define __float64_expo_from_float32__(X)    ((X - FLOAT32_EXPO_BASE + FLOAT64_EXPO_BASE)&FLOAT64_EXPO_MASK)
#define __float64_lo_from_float32__(X)      ((X&FLOAT32_TO64_FRAC_LO_MASK)<<29)
#define __float64_hi_from_float32__(S,E,F)  ((S << FLOAT32_SIGN_POS)|(E<<FLOAT64_EXPO_HI_POS)|((F&FLOAT32_TO64_FRAC_HI_MASK)>>3))
// float64 to float32
#define __float32_expo_from_float64__(X)    ((((X>>FLOAT64_EXPO_HI_POS)&FLOAT32_EXPO_MASK) - FLOAT64_EXPO_BASE + FLOAT32_EXPO_BASE)&FLOAT32_EXPO_MASK)
#define __float32_frac_from_float64__(H,L)  (((H&FLOAT32_TO64_FRAC_HI_MASK)<<3)|((L>>29)&FLOAT32_TO64_FRAC_LO_MASK)|0x00800000)
// For float64
unsigned long __float64_buffer[2];
#define __float64_buffer_hi     __float64_buffer[1]
#define __float64_buffer_lo     __float64_buffer[0]
#define __float64_buffer_to_float64__()      (*((double*)__float64_buffer))
/*! \endcond */

/**
 * @brief Calculate the negative value of a_fp.
 * @param a_fp The value to calculate.
 * @return The negative value of a_fp.
 */
float fp_float32_neg(float a_fp)
{
    uint32_t a;
    a = __float32_to_uint32__(a_fp);
    a ^= 0x80000000;
    return __uint32_to_float32__(a);
}

/**
 * @brief           Calculate absolute value.
 * @param a_fp      The value to calculate absolute value.
 * @return float    The absolute value of a_fp.
 */
float fp_float32_abs(float a_fp)
{
    if (fp_float32_cmp(a_fp, 0) == -1 ) {
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
float fp_float32_add(float a_fp, float b_fp)
{
    uint32_t a,b,c;             // unit32 expression
    uint32_t as,bs,cs;          // sign
    int32_t ae,be,ce,af,bf,cf;  // exponent and fraction
    a = __float32_to_uint32__(a_fp);
    b = __float32_to_uint32__(b_fp);
    as = __float32_sign__(a);            //sign
    ae = __float32_expo__(a);            //exponent
    af = __float32_frac__(a);            //fraction
    bs = __float32_sign__(b);
    be = __float32_expo__(b);
    bf = __float32_frac__(b);
    if(ae > be) {                    // align the fraction according to the exponent
        if(ae - be < 24)            // exponent difference bigger than 24 result in precision lost
            bf >>= ae - be;
        else
            bf = 0;
        ce = ae;
    } else {
        if(be - ae < 24)
            af >>= be - ae;
        else
            af = 0;
        ce = be;
    }
    cf = (as ? -af : af) + (bs ? -bf : bf);     // calculate the fraction of the sum.
    cs = cf < 0;
    cf = cf>=0 ? cf : -cf;
    if(cf == 0) return __uint32_to_float32__(cf);
    while(cf & FLOAT32_REIGHT_SHIFT_MASK) {     // correct the mantissa, 24 bits at most
        ++ce;         // fraction right shift
        cf >>= 1;
    }
    while((cf & FLOAT32_LEFT_SHIFT_MASK) == 0) {         // Bit23 must be 1.
        --ce;
        cf <<= 1;
    }
    c = __assemble_float32__(cs,ce,cf);
    if(ce < 1) c = 0;
    return __uint32_to_float32__(c);
}


/**
 * @brief Subtraction arithmetic operation.
 * @param a_fp The minuend.
 * @param b_fp The subtrahend.
 * @return The result.
 */
float fp_float32_sub(float a_fp, float b_fp)
{
    return fp_float32_add(a_fp, fp_float32_neg(b_fp));
}

/**
 * @brief Multiplication.
 * @param a_fp The number 1 to multiply.
 * @param b_fp The number 2 to multiply.
 * @return The product.
 */
float fp_float32_mult(float a_fp, float b_fp)
{
    uint32_t a,b,c;             // unit32 expression
    uint32_t as,bs,cs;          // sign
    int32_t ae,be,ce,af,bf,cf;  // exponent and fraction
    uint32_t a1,a2,b1,b2,med1,med2,lo,hi;   // for multiply
    // conversion
    a = __float32_to_uint32__(a_fp);
    b = __float32_to_uint32__(b_fp);
    as = __float32_sign__(a);            //sign
    ae = __float32_expo__(a);            //exponent
    af = __float32_frac__(a);            //fraction
    bs = __float32_sign__(b);
    be = __float32_expo__(b);
    bf = __float32_frac__(b);
    // calculation
    cs = as ^ bs;                               // calculate sign
    a1 = af & 0xffff;                           // low 16 bits of af
    a2 = af >> 16;                              // high 16 bits of bf
    b1 = bf & 0xffff;                           // low 16 bits of af
    b2 = bf >> 16;                              // high 16 bits of bf
    lo = a1 * b1;                               // low part, starts from bit0
    med1 = a2 * b1 + (lo >> 16);                // cross part1, starts from bit16
    med2 = a1 * b2;                             // cross part2, starts from bit16
    hi = a2 * b2 + (med1 >> 16) + (med2 >> 16);     // high part, starts from bit32
    med1 = (med1 & 0xffff) + (med2 & 0xffff);     // calculate carry-over
    hi += (med1 >> 16);                         // add carry-over, high part calculated
    lo = (med1 << 16) | (lo & 0xffff);          // low part calculated
    cf = (hi << 9) | (lo >> 23);                // fraction calculated
    /** Actual fraction in calculation has 24 bits, and hi uses 16 bits at most.
     * What's more, bit15 is the exceeding bit, so it should be moved to bit24.
     */
    ce = ae + be - FLOAT32_EXPO_BASE + 1;                    // exponent calculated
    if(cf == 0) return __uint32_to_float32__(cf);
    while(cf & FLOAT32_REIGHT_SHIFT_MASK) {
        ++ce;
        cf >>= 1;
    }
    c = __assemble_float32__(cs,ce,cf);
    if(ce < 1) c = 0;
    return __uint32_to_float32__(c);
}

/**
 * @brief Float Division.
 *
 * @param a_fp Dividend.
 * @param b_fp Divisor.
 * @return float Quotient.
 */
float fp_float32_div(float a_fp, float b_fp)
{
    uint32_t a,b,c;             // unit32 expression
    uint32_t as,bs,cs;          // sign
    int32_t ae,be,ce,af,bf,cf;  // exponent and fraction
    uint32_t a1,a2,b1,b2,med1,med2,lo,hi;   // for division
    int32_t d;
    a = __float32_to_uint32__(a_fp);
    b = __float32_to_uint32__(b_fp);
    as = __float32_sign__(a);            //sign
    ae = __float32_expo__(a);            //exponent
    af = __float32_frac__(a);            //fraction
    bs = __float32_sign__(b);
    be = __float32_expo__(b);
    bf = __float32_frac__(b);

    cs = as ^ bs;                               // calculate sign
    ce = ae - (be - 0x80) + 6 - 8;
    a1 = af << 4;     //8                           // magnify
    b1 = bf >> 8;                               // ignore low 8-bit, it doesn't influence precision
    cf = a1 / b1;                               // calculate the quotient
    cf <<= 12;     //8                              // rescale to 24 bits
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

    if(cf == 0) return __uint32_to_float32__(cf);
    while(cf & FLOAT32_REIGHT_SHIFT_MASK) {
        ++ce;
        cf >>= 1;
    }
    if(ce < 0) ce = 0;
    c = __assemble_float32__(cs,ce,cf);
    if(ce < 1) c = 0;
    return __uint32_to_float32__(c);
}

/**
 * @brief Convert float to signed long.
 *
 * @param a_fp float to be converted to long.
 * @return long the long integer.
 */
long fp_float32_to_int32(float a_fp)
{
    uint32_t a;     // uint32_t expression
    uint32_t as;    // sign
    int32_t ae, af; // exponent and fraction
    long shift;
    a = __float32_to_uint32__(a_fp);
    as = __float32_sign__(a);            //sign
    ae = __float32_expo__(a);            //exponent
    af = __float32_frac__(a);            //fraction

    af <<= 7;
    shift = -(ae - FLOAT32_EXPO_BASE - 29);
    if(shift > 0) {
        if(shift < 31)
            af >>= shift;
        else
            af = 0;
    }
    af = as ? -af : af;
    return af;
}

/**
 * @brief Convert signed long to float.
 *
 * @param af long value to be converted to float.
 * @return float the float.
 */
float fp_int32_to_float32(long af)
{
    uint32_t a;  // unit32 expression
    uint32_t as; // sign
    int32_t ae;  // exponent
    as = af>=0 ? 0 : 1;
    af = af>=0 ? af : -af;
    ae = FLOAT32_EXPO_BASE + 22;
    if(af == 0)
        return __uint32_to_float32__(af);
    while(af & FLOAT32_REIGHT_SHIFT_MASK) {
        ++ae;
        af >>= 1;
    }
    while((af & FLOAT32_LEFT_SHIFT_MASK) == 0) {
        --ae;
        af <<= 1;
    }
    a = __assemble_float32__(as, ae, af);
    return __uint32_to_float32__(a);
}

/**
 * @brief Convert unsigned long to float.
 *
 * @param af unsigned long value to be converted to float.
 * @return float the float.
 */
float fp_uint32_to_float32(unsigned long af)
{
    uint32_t a;  // unit32 expression
    uint32_t as; // sign
    int32_t ae;  // exponent
    as = 0;
    ae = FLOAT32_EXPO_BASE + 22;    // FLOAT32_EXPO_BASE - 1 + 23
    if(af == 0)
        return __uint32_to_float32__(af);
    while(af & FLOAT32_REIGHT_SHIFT_MASK) {
        ++ae;
        af >>= 1;
    }
    while((af & FLOAT32_LEFT_SHIFT_MASK) == 0) {
        --ae;
        af <<= 1;
    }
    a = __assemble_float32__(as, ae, af);
    return __uint32_to_float32__(a);
}

/*! \cond PRIVATE */
/**
 * @brief Convert float32 to float64.
 *
 * @param a_fp float32 value to be converted to float64.
 * @return double the float64.
 */
double fp_float32_to_float64(float a_fp)
{
    uint32_t a;             // unit32 expression
    uint32_t as,bs;          // sign
    int32_t ae,be,af;  // exponent and fraction
    a = __float32_to_uint32__(a_fp);
    as = __float32_sign__(a);
    ae = __float32_expo__(a);
    af = __float32_frac__(a);

    bs = as;
    be = __float64_expo_from_float32__(ae);
    __float64_buffer_lo = __float64_lo_from_float32__(af);
    __float64_buffer_hi = __float64_hi_from_float32__(bs, be, af);
    return __float64_buffer_to_float64__();
}

/**
 * @brief Convert float64 to float32.
 *
 * @param a_dfp float64 value to be converted to float32.
 * @return float the float32.
 */
float fp_float64_to_float32(double a_dfp)
{
    uint32_t a;             // unit32 expression
    uint32_t as;          // sign
    int32_t ae,af;  // exponent and fraction
    __float64_buffer_hi = __float64_hi(a_dfp);
    __float64_buffer_lo = __float64_lo(a_dfp);
    as = __float32_sign__(__float64_buffer_hi);
    ae = __float32_expo_from_float64__(__float64_buffer_hi);
    if (ae >= 256) {
        return FLOAT32_NaN();
    } else if (ae <= 0) {
        return fp_int32_to_float32(0);
    } else {    // 0 < ae < 256
        af = __float32_frac_from_float64__(__float64_buffer_hi, __float64_buffer_lo);
        a = __assemble_float32__(as,ae,af);
        float a_fp = __uint32_to_float32__(a);
        return a_fp;
    }
}

double fp_float64_add(double a_dfp, double b_dfp)
{
    return fp_float32_add(fp_float64_to_float32(a_dfp), fp_float64_to_float32(b_dfp));
}

double fp_float64_sub(double a_dfp, double b_dfp)
{
    return fp_float32_sub(fp_float64_to_float32(a_dfp), fp_float64_to_float32(b_dfp));
}

double fp_float64_mult(double a_dfp, double b_dfp)
{
    return fp_float32_mult(fp_float64_to_float32(a_dfp), fp_float64_to_float32(b_dfp));
}

double fp_float64_div(double a_dfp, double b_dfp)
{
    return fp_float32_div(fp_float64_to_float32(a_dfp), fp_float64_to_float32(b_dfp));
}
/*! \endcond */

//0 iff a==b; 1 iff a>b; -1 iff a<b
/**
 * @brief Compare two float value.
 *
 * @param a_fp float value a.
 * @param b_fp float value b.
 * @return int  0 if a==b; 1 if a>b; -1 if a<b;
 */
int fp_float32_cmp(float a_fp, float b_fp)
{
    unsigned long a, b;
    unsigned long as, ae, af, bs, be, bf;
    int gt;
    a = __float32_to_uint32__(a_fp);
    b = __float32_to_uint32__(b_fp);
    //      puts("cmp: a="); print_hex(a); puts(" b="); print_hex(b);
    if(a == b)
        return 0;
    as = __float32_sign__(a);
    bs = __float32_sign__(b);
    if(as > bs)     // as < 0, bs >=0, so a_fp < b_fp
        return -1;
    if(as < bs)
        return 1;
    gt = as ? -1 : 1;
    ae = __float32_expo__(a);
    be = __float32_expo__(b);
    if(ae > be)
        return gt;
    if(ae < be)
        return -gt;
    af = __float32_frac__(a);
    bf = __float32_frac__(b);
    if(af > bf)
        return gt;
    return -gt;
}

/*! \cond PRIVATE */
int __ltsf2(float a_fp, float b_fp)
{
    return fp_float32_cmp(a_fp, b_fp);
}

int __lesf2(float a_fp, float b_fp)
{
    return fp_float32_cmp(a_fp, b_fp);
}

int __gtsf2(float a_fp, float b_fp)
{
    return fp_float32_cmp(a_fp, b_fp);
}

int __gesf2(float a_fp, float b_fp)
{
    return fp_float32_cmp(a_fp, b_fp);
}

int __eqsf2(float a_fp, float b_fp)
{
    return __float32_to_uint32__(a_fp) != __float32_to_uint32__(b_fp);
}

int __nesf2(float a_fp, float b_fp)
{
    return __float32_to_uint32__(a_fp) != __float32_to_uint32__(b_fp);
}
/*! \endcond */

/**
 * @brief Returns the square root of x.
 *
 * @param x Value whose square root is computed.
 * @return float Square root of x.If x < 0, return 0.
 */
float fp_float32_sqrt(float x)
{
    float x1, y1, x2, y2, x3;
    long i;
    if (x < 0) return 0;
    x1 = fp_int32_to_float32(1);
    y1 = fp_float32_sub(fp_float32_mult(x1, x1), x);     //y1=x1*x1-a;
    x2 = fp_int32_to_float32(100);
    y2 = fp_float32_sub(fp_float32_mult(x2, x2), x);
    for(i = 0; i < 10; ++i) {
        if(__float32_to_uint32__(y1) == __float32_to_uint32__(y2))
            return x2;
        //x3=x2-(x1-x2)*y2/(y1-y2);
        x3 = fp_float32_sub(x2, fp_float32_div(fp_float32_mult(fp_float32_sub(x1, x2), y2), fp_float32_sub(y1, y2)));
        x1 = x2;
        y1 = y2;
        x2 = x3;
        y2 = fp_float32_sub(fp_float32_mult(x2, x2), x);
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
float fp_float32_cos(float rad)
{
    int n;
    float answer, x2, top, bottom, sign;
    while(fp_float32_cmp(rad, TWO_PI) > 0) {
        rad = fp_float32_sub(rad, TWO_PI);
    }
    while(fp_float32_cmp(rad, (float)0.0) < 0) {
        rad = fp_float32_add(rad, TWO_PI);
    }

    answer = fp_int32_to_float32(1);
    sign = fp_int32_to_float32(1);

    if(fp_float32_cmp(rad, PI) >= 0) {
        rad = fp_float32_sub(rad, PI);
        sign = fp_int32_to_float32(-1);
    }
    if(fp_float32_cmp(rad, HALF_PI) >= 0) {
        rad = fp_float32_sub(PI, rad);
        sign = fp_float32_neg(sign);
    }
    x2 = fp_float32_mult(rad, rad);
    top = fp_int32_to_float32(1);
    bottom = fp_int32_to_float32(1);
    for(n = 2; n < 12; n += 2) {
        top = fp_float32_mult(top, fp_float32_neg(x2));
        bottom = fp_float32_mult(bottom, fp_int32_to_float32((n - 1) * n));
        answer = fp_float32_add(answer, fp_float32_div(top, bottom));
    }
    return fp_float32_mult(answer, sign);
}

/**
 * @brief Returns the sine of an angle of x radians.
 *
 * @param rad Value representing an angle expressed in radians.
 * @return float Sine of x radians.
 */
float fp_float32_sin(float rad)
{
    return fp_float32_cos(fp_float32_sub(rad, HALF_PI));
}

/**
 * @brief Returns the principal value of the arc tangent of x, expressed in radians.
 *
 * @param x Value whose arc tangent is computed.
 * @return float Principal arc tangent of x, in the interval [-pi/2,+pi/2] radians.One radian is equivalent to 180/PI degrees.
 */
float fp_float32_atan(float x)
{
    //float b = fp_float32_div(PI, fp_int32_to_float32(800000000));
    //float atan_b = fp_float32_div(fp_int32_to_float32(37419668), fp_int32_to_float32(100000000));
    int n;
    float answer, x2, top;
    if(fp_float32_cmp(x, fp_int32_to_float32(0)) >= 0) {
        if(fp_float32_cmp(x, fp_int32_to_float32(1)) > 0)
            return fp_float32_sub(HALF_PI, fp_float32_atan(fp_float32_div(fp_int32_to_float32(1), x)));
    }
    else {
        if(fp_float32_cmp(x, fp_int32_to_float32(-1)) > 0)
            return fp_float32_sub(-HALF_PI, fp_float32_atan(fp_float32_div(fp_int32_to_float32(1), x)));
    }
    if(fp_float32_cmp(x, fp_float32_div(fp_int32_to_float32(45), fp_int32_to_float32(100))) > 0) {
        answer = fp_float32_div(fp_float32_sub(x, ATAN_EIGHTH_PI), fp_float32_add(fp_int32_to_float32(1), fp_float32_mult(x, ATAN_EIGHTH_PI)));
        answer = fp_float32_sub(fp_float32_add(EIGHTH_PI, fp_float32_atan(answer)), fp_float32_div(fp_int32_to_float32(34633), fp_int32_to_float32(1000000)));
        return answer;
    }
    if(fp_float32_cmp(x, fp_float32_div(fp_int32_to_float32(-45), fp_int32_to_float32(100))) < 0) {
        x = fp_float32_neg(x);
        answer = fp_float32_div(fp_float32_sub(x, ATAN_EIGHTH_PI), fp_float32_add(fp_int32_to_float32(1), fp_float32_mult(x, ATAN_EIGHTH_PI)));
        answer = fp_float32_sub(fp_float32_add(EIGHTH_PI, fp_float32_atan(answer)), fp_float32_div(fp_int32_to_float32(34633), fp_int32_to_float32(1000000)));
        return fp_float32_neg(answer);
    }
    answer = x;
    x2 = fp_float32_mult(fp_float32_neg(x), x);
    top = x;
    for(n = 3; n < 14; n += 2) {
        top = fp_float32_mult(top, x2);
        answer = fp_float32_add(answer, fp_float32_div(top, fp_int32_to_float32(n)));
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
float fp_float32_atan2(float y, float x)
{
    float answer,r;
    if ( x == 0 ) return 0;
    r = y / x;
    answer = fp_float32_atan(r);
    if(fp_float32_cmp(x, fp_int32_to_float32(0)) < 0) {
        if(fp_float32_cmp(y, fp_int32_to_float32(0)) > 0)
            answer = fp_float32_add(answer, PI);
        else
            answer = fp_float32_sub(answer, PI);
    }
    return answer;
}

/**
 * @brief Returns the base-e exponential function of x, which is e raised to the power x.
 *
 * @param x   Value of the exponent.
 * @return float  Exponential value of x.
 */
float fp_float32_exp(float x)
{
    //float E_SQUARE     = fp_float32_div(fp_int32_to_float32(738905609), fp_int32_to_float32(100000000));
    //float inv_E_SQUARE = fp_float32_div(fp_int32_to_float32(13533528), fp_int32_to_float32(100000000));
    float answer, top, bottom, mult;
    int n;

    mult = fp_int32_to_float32(1);
    while(fp_float32_cmp(x, fp_int32_to_float32(2)) > 0) {
        mult = fp_float32_mult(mult, E_SQUARE);
        x = fp_float32_add(x, fp_int32_to_float32(-2));
    }
    while(fp_float32_cmp(x, fp_int32_to_float32(-2)) < 0) {
        mult = fp_float32_mult(mult, INV_E_SQUARE);
        x = fp_float32_add(x, fp_int32_to_float32(2));
    }
    answer = fp_float32_add(fp_int32_to_float32(1), x);
    top = x;
    bottom = fp_int32_to_float32(1);
    for(n = 2; n < 15; ++n) {
        top = fp_float32_mult(top, x);
        bottom = fp_float32_mult(bottom, fp_int32_to_float32(n));
        answer = fp_float32_add(answer, fp_float32_div(top, bottom));
    }
    return fp_float32_mult(answer, mult);
}

/**
 * @brief The natural logarithm is the base-e logarithm: the inverse of the natural exponential function (fp_float32_exp).
 *
 * @param x  Value whose logarithm is calculated.
 * @return float Natural logarithm of x. If x <= 0, return 0.
 */
float fp_float32_log(float x)
{
    //float log_2       = fp_float32_div(fp_int32_to_float32(69314718), fp_int32_to_float32(100000000)); //LN_2
    //float num_1p5     = fp_float32_div(fp_int32_to_float32(15), fp_int32_to_float32(10));      // 1.5
    //float num_0p5     = fp_float32_div(fp_int32_to_float32(5), fp_int32_to_float32(10));       // 0.5
    //float num_0p0625  = fp_float32_div(fp_int32_to_float32(625), fp_int32_to_float32(10000));  // 0.0625

    int n;
    float answer, top, add;
    if (x <= 0) return 0;      // the value is negative, error!
    add = fp_int32_to_float32(0);
    while(fp_float32_cmp(x, fp_int32_to_float32(16)) > 0) {
        x = fp_float32_mult(x, 0.0625);
        add = fp_float32_add(add, fp_float32_mult(LN_2, fp_int32_to_float32(4)));
    }
    while(fp_float32_cmp(x, 1.5) > 0) {
        x = fp_float32_mult(x, 0.5);
        add = fp_float32_add(add, LN_2);
    }
    while(fp_float32_cmp(x, 0.5) < 0) {
        x = fp_float32_mult(x, fp_int32_to_float32(2));
        add = fp_float32_sub(add, LN_2);
    }
    x = fp_float32_sub(x, fp_int32_to_float32(1));
    answer = fp_int32_to_float32(0);
    top = fp_int32_to_float32(-1);
    for(n = 1; n < 14; ++n) {
        top = fp_float32_mult(top, fp_float32_neg(x));
        answer = fp_float32_add(answer, fp_float32_div(top, fp_int32_to_float32(n)));
    }
    return fp_float32_add(answer, add);
}

/**
 * @brief Compute power.
 *
 * @param x  Base value.
 * @param y  Exponent value.
 * @return float  The result of raising base to the power exponent.
 */
float fp_float32_pow(float x, float y)
{
    return fp_float32_exp(y * fp_float32_log(x));
}

/********************************************/
//These five functions will only be used if the flag "-mno-mul" is enabled
#ifdef USE_SW_MULT
unsigned long __mulsi3(unsigned long a, unsigned long b)
{
    unsigned long answer = 0;
    while(b) {
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
    for(i = 0; i < 32; ++i) {
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
    if(a < 0) {
        a = -a;
        negate = !negate;
    }
    if(b < 0) {
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
