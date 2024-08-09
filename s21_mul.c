#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){
    int res = ARITHMETIC_OK;
    int error = 0;

    if (is_zero(value_1) || is_zero(value_2)){
        clear_s21_decimal(result);
    }
    else{
        big_decimal tmp;

        mul_mantis(value_1, value_2, &tmp);
        getoverflow(&tmp);
        error = normalize(&tmp);

        if (!error){
            big_decimal_to_decimal(tmp, result);
            if (is_minus(value_1) != is_minus(value_2))
                set_minus(result);
        }
        else
            res = is_minus(value_1) != is_minus(value_2) ? TOO_SMALL : TOO_LARGE;
    }
    return res;
}
