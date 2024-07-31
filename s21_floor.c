#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result){
    big_decimal tmp;
    int remainder = 0;
    int scale = (value.bits[3] & SC) >> 16;

    if (scale == 0){
        *result = value;
    }
    else{
        decimal_to_big_decimal(value, &tmp);

        for (int i = 0; i < scale; i++){
            remainder = scale_down(&tmp);
        }
        if (is_minus(value) && remainder)
            tmp.bits[0] += 1;

        clear_s21_decimal(result);
        big_decimal_to_decimal(tmp, result);

        if (is_minus(value)){
            set_minus(result);

            if (is_zero(*result))
                s21_negate(*result, result);
        }
    }
    return 0;
}
