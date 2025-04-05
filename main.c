#include <stdio.h>
#include "pico/stdlib.h"
#include "fr_types.h"

#pragma GCC "-O0"
int main()
{
    stdio_init_all();
    int counter = 0;
    fr16_type a16, b16, res16, res2_16, one_tenth16;

    while (true) {
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
