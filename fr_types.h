#include "limits.h"

/**
 * @headerfile
 * @brief This is the header file for the "fractional" datatype. 
 * @details fr_type is S1.31 with range [-1, 1) with LSB = 2^-31 = 46.5661287x10^(-9)
 * @cite Applied Control Theory for Embedded Systems by Tim Wescott
 */

typedef int fr_type;  //! S1.31      [-32768, 32768) LSB = 152.6x10^-3 = 2^(-16)

/* Macros */
#define FR_SHIFT (sizeof(fr_type) * CHAR_BIT -1)  //! FR_SHIFT=31 (sizeof() returns the # of chars, hence the multiply by CHAR_BIT)
#define FLOAT_DIV ((double)INT_MAX + 1)         //! FLOAT_DIV=2.147484e+09 = rounded((1<<31))

/* Function Definitions */
fr_type sat_add(fr_type a, fr_type b);      // Add and saturate
fr_type sat_sub(fr_type a, fr_type b);      // Subtract and saturate (a-b)
fr_type sat_mul(fr_type a, fr_type b);      // Multiply and saturate
fr_type fr_mul(fr_type a, fr_type b);       // Multiply by fractional value
fr_type div_to_int(fr_type a, fr_type b);   // Divide to integer value (a/b)
fr_type div_to_fr(int a, int b);    // Divide to fractional value (a/b)
fr_type make_fr(double a);                  // make from float
double get_fr(fr_type a);                   // extract float

/*  Next Type   */
typedef int fr16_type;  //! S16.16 [-32768, 32768) LSB = 1.52587890625e-5 = 2^(-16)

/* Macros */
#define FR16_SHIFT 16  //! Fixed point position at bit 16
#define FR16_FLOAT_DIV (1 << FR16_SHIFT)  //! FLOAT_DIV=65536 = 2^16

/* Function Definitions */
fr16_type sat_add16(fr16_type a, fr16_type b);      // Add and saturate
fr16_type sat_sub16(fr16_type a, fr16_type b);      // Subtract and saturate (a-b)
fr16_type sat_mul16(fr16_type a, fr16_type b);      // Multiply and saturate
fr16_type fr_mul16(fr16_type a, fr16_type b);       // Multiply by fractional value
fr16_type div_to_int16(fr16_type a, fr16_type b);   // Divide to integer value (a/b)
fr16_type div_to_fr16(int a, int b);                // Divide to fractional value (a/b)
fr16_type make_fr16(double a);                      // make from float
double get_fr16(fr16_type a);                       // extract float