#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst){
    int res = 0;

    if (dst != NULL){
        if (src < 0){
            set_minus(dst);
            src = -src;
        }
        clear_s21_decimal(dst);
        dst->bits[0] = src;
    }
    else
        res = 1;

    return res;
}
