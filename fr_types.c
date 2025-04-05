#include "fr_types.h"
#include <math.h>
#include <stdint.h>

fr_type sat_add(fr_type a, fr_type b) {
    fr_type retval = a + b; //perform regular addition

    //check for rollover, if so saturate
    if(a<0 && b<0) {
        if(retval > 0 || retval < -INT_MAX) retval = -INT_MAX;
    } else if(a > 0 && b > 0 && retval < 0) retval = INT_MAX;
    return retval;
}
fr_type sat_sub(fr_type a, fr_type b) {
    fr_type retval = a - b; //perform regular subtraction

    //check for rollover, if so saturate
    if(a < 0 && b > 0) { //! if negative portion is greater than positive portion
        if(retval > 0 || retval < -INT_MAX) retval = -INT_MAX;
    } else if(a > 0 && b < 0 && retval < 0) retval = INT_MAX;
    return retval;
}

fr_type sat_mul(fr_type a, fr_type b) {
    //Perform a multiply, ensure the result can hold the overflow
    long long result = (long long)a * (long long)b;

    // Check for rollover and if so, saturate
    if(result > INT_MAX) result = INT_MAX;
    if(result < -INT_MAX) result = -INT_MAX;
    return result; 
}

fr_type fr_mul(fr_type a, fr_type b) {
    long long result = (long long)a * (long long)b;
    //< the book says no overflow checking is necessary here
    return (result >> FR_SHIFT);
}

fr_type div_to_int(fr_type a, fr_type b) {
    if(b == 0) return 0; // handles divide by 0
    return (sat_add(a, b/2) / b); // Round, Divide, Return
}

fr_type div_to_fr(int a, int b) {
    if(b==0) return 0;      // Bomb if illegal divide

    // Shift 'a' up to simulate a fractional value
    long long result = (long long)a << FR_SHIFT;
    result /= (long long)b;

    // Check for rollover and saturate if so
    if(result > INT_MAX) result = INT_MAX;
    if(result < -INT_MAX) result = -INT_MAX;

    return result;
}

fr_type make_fr(double a) {
    a = a*FLOAT_DIV+0.5; // add 0.5 so that floor() rounds the number instead of merely truncating
    //! eg. 1+0.5 will round to 1 but 1.5+0.5 will round to 2. 
    a = floor(a);       // remove decimal place & round
    if(a > INT_MAX) return INT_MAX;
    else if (a < -INT_MAX) return -INT_MAX;

    return (fr_type)a; 
}
double get_fr(fr_type a) {
    return a/FLOAT_DIV;
}

/* Next Type: S16.16 */
// S16.16 implementation
fr16_type sat_add16(fr16_type a, fr16_type b) {
    int64_t sum = (int64_t)a + b;
    if (sum > INT32_MAX) return INT32_MAX;
    if (sum < INT32_MIN) return INT32_MIN;
    return (fr16_type)sum;
}

fr16_type sat_sub16(fr16_type a, fr16_type b) {
    int64_t diff = (int64_t)a - b;
    if (diff > INT32_MAX) return INT32_MAX;
    if (diff < INT32_MIN) return INT32_MIN;
    return (fr16_type)diff;
}

fr16_type sat_mul16(fr16_type a, fr16_type b) {
    int64_t product = ((int64_t)a * b) >> FR16_SHIFT;
    if (product > INT32_MAX) return INT32_MAX;
    if (product < INT32_MIN) return INT32_MIN;
    return (fr16_type)product;
}

fr16_type fr_mul16(fr16_type a, fr16_type b) {
    return (fr16_type)(((int64_t)a * b) >> FR16_SHIFT);
}

fr16_type div_to_int16(fr16_type a, fr16_type b) {
    if (b == 0) return 0;
    return (fr16_type)((int64_t)a << FR16_SHIFT) / b;
}

fr16_type div_to_fr16(int a, int b) {
    if (b == 0) return 0;
    return (fr16_type)((int64_t)a << FR16_SHIFT) / b;
}

fr16_type make_fr16(double a) {
    return (fr16_type)(a * FR16_FLOAT_DIV);
}

double get_fr16(fr16_type a) {
    return (double)a / FR16_FLOAT_DIV;
}