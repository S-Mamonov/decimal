#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst){
    double tmp = 0;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 32; j++)
            tmp += ((src.bits[i] >> j) & 1) * pow(2, 32 * i + j);

    tmp /= pow(10, (src.bits[3] & SC) >> 16);

    if (is_minus(src))
        tmp = -tmp;

    *dst = tmp;

    return 0;
}
