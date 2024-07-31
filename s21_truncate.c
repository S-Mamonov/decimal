#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result){
    big_decimal tmp;
    int scale = (value.bits[3] & SC) >> 16;;

    if (scale == 0){
        *result = value;
    }
    else{
        decimal_to_big_decimal(value, &tmp);

        for (int i = 0; i < scale; i++)
            scale_down(&tmp);

        clear_s21_decimal(result);
        big_decimal_to_decimal(tmp, result);

        if (is_minus(value))
            set_minus(result);
    }
    return 0;
}
