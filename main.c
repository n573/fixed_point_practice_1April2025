#include <stdio.h>
#include "pico/stdlib.h"
#include "fr_types.h"

#define VSx_GAIN 0.076212f
// 12V * VSx_GAIN = 0.914544

#define R_SHUNT 0.05f
#define SHUNT_AMPLIFIER_GAIN 10

#define ADC_RAW_CAL (4.096/65536)

#pragma GCC "-O0"
int main()
{
    stdio_init_all();
    int counter = 0;
    fr16_type a16, b16, res16, res2_16, one_tenth16;
    fr16_type gain_correction = make_fr16(1.0/VSx_GAIN);
    fr16_type read_volts = make_fr16(0.914544);
    uint16_t read_shunt_val = 46400; // Estimated using 65535*(2.9/4.096)
    fr16_type read_val = make_fr16((float)(read_shunt_val - 0x7FFF)*ADC_RAW_CAL); // 0x7FFF is the midpoint value
    // fr16_type read_val = make_fr16((float)(read_shunt_val*ADC_RAW_CAL - 2.048)); // 2.048f is the midpoint value -- same as int implementation ^ 
    // fr16_type shunt_inv = make_fr(1.0/R_SHUNT);
    // fr16_type amp_gain_inv = make_fr(1.0/SHUNT_AMPLIFIER_GAIN);
    fr16_type shunt_inv = make_fr16(1.0/R_SHUNT);
    fr16_type amp_gain_inv = div_to_fr16(1.0, SHUNT_AMPLIFIER_GAIN);

    while (true) {
        /* Current Measurement */
        /**
         * read value, subtract midpoint value, then..
         * make it S16.16 format..
         * multiply by 1/10 for the amplifier gain
         * multiply by 1/Rshunt for Ohms Law
         */
        printf("U16.0: %d, S16.16: %i => %f\n", read_shunt_val-0x7FFF, read_val, get_fr16(read_val));
        printf("1/0.05 = 20 => %i = %f\n 1/10 = 0.1 => %i = %f\n", shunt_inv, get_fr16(shunt_inv), amp_gain_inv, get_fr16(amp_gain_inv));
        a16 = fr_mul16(read_val, shunt_inv);
        b16 = fr_mul16(a16, amp_gain_inv);
        printf("S16.16 %f * %f * %f = %f\n", get_fr16(read_val), get_fr16(shunt_inv), get_fr16(amp_gain_inv), get_fr16(b16));

        /* Voltage Measurement*/
        res16 = fr_mul16(read_volts, gain_correction);
        printf("S16.16 %f * %f = %f\n", get_fr16(read_volts), get_fr16(gain_correction), get_fr16(res16));

        /* OLD TESTS */
        a16 = counter + make_fr16(0.5);
        b16 = counter + make_fr16(0.25);
        res16 = sat_add16(a16, b16);
        printf("S16.16: %f + %f = %f\n", get_fr16(a16), get_fr16(b16), get_fr16(res16));
        
        res16 = sat_sub16(b16, a16);
        printf("S16.16: %f - %f = %f\n", get_fr16(b16), get_fr16(a16), get_fr16(res16));
        
        res2_16 = fr_mul16(a16, res16);
        printf("S16.16: %f * %f = %f\n", get_fr16(a16), get_fr16(res16), get_fr16(res2_16));
        
        one_tenth16 = div_to_fr16(1, 10);
        printf("S16.16: 1/10 = %f\n", get_fr16(one_tenth16));
        
        res16 = fr_mul16(one_tenth16, res2_16);
        printf("S16.16: %f * %f = %f\n", get_fr16(one_tenth16), get_fr16(res2_16), get_fr16(res16));
        
        res2_16 = fr_mul16(one_tenth16, res16);
        printf("S16.16: %f * %f = %f\n", get_fr16(one_tenth16), get_fr16(res16), get_fr16(res2_16));

        res2_16 = fr_mul16(make_fr16(20.0), res16);
        printf("S16.16: %f * %f = %f\n", get_fr16(make_fr16(20.0)), get_fr16(res16), get_fr16(res2_16));

        sleep_ms(5000);
        counter += make_fr16(1.0);
        puts("\n");
    }
    
    // fr_type counter = make_fr(1.0f);
    /* fr_type a, b, res, res2, one_tenth;
    while (true) {
        // a = make_fr(counter * 0.5f);
        // b = make_fr(counter * 0.25f);
        a = counter + make_fr(0.5f);
        b = counter + make_fr(0.25f);
        res = sat_add(a,b);
        printf("%f + %f = %f\n", get_fr(a), get_fr(b), get_fr(res));
        res = sat_sub(b,a);
        printf("%f + %f = %f\n", get_fr(a), get_fr(b), get_fr(res));
        res2 = fr_mul(a, res);
        printf("%f + %f = %f\n", get_fr(a), get_fr(res), get_fr(res2));
        // printf("Hello, world!\n");
        one_tenth = div_to_fr(1, 10); 
        printf("1/10 = %f\n", get_fr(one_tenth));
        res = fr_mul(one_tenth, res2);
        printf("%f + %f = %f\n", get_fr(one_tenth), get_fr(res2), get_fr(res));
        res2 = fr_mul(one_tenth, res);
        printf("%f + %f = %f\n", get_fr(one_tenth), get_fr(res), get_fr(res2));

        sleep_ms(5000);
        // counter++;
        counter += make_fr(1.0);
        puts("\n");
    } */
}
