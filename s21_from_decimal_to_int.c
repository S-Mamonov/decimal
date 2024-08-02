#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst){
    int res = 0;

    s21_truncate(src, &src);

    if (src.bits[2] || src.bits[1]){
        res = 1;
    }
    else{
        if (!is_minus(src)){
            if ((unsigned int)src.bits[0] > 2147483647){
                res = 1;
            }
            else
                *dst = src.bits[0];
        }
        else{
            if ((unsigned int)src.bits[0] > 2147483648){
                res = 1;
            }
            else
                *dst = -src.bits[0];
        }
    }
    return res;
}
