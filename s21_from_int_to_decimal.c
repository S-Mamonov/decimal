#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst){
    clear_s21_decimal(dst);

    if (src < 0){
        set_minus(dst);
        src = -src;
    }
    dst->bits[0] = src;

    return 0;
}
