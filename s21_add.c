#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){
    int res = ARITHMETIC_OK;
    int error = 0;

    if (is_zero(value_1) && is_zero(value_2)){
        clear_s21_decimal(result);
    }
    else if (is_zero(value_1)){
        *result = value_2;
    }
    else if (is_zero(value_2)){
        *result = value_1;
    }
    else{
        if ((!is_minus(value_1) && !is_minus(value_2)) || (is_minus(value_1) && is_minus(value_2))){
            big_decimal tmp;

            add_mantis(value_1, value_2, &tmp);
            getoverflow(&tmp);
            error = normalize(&tmp);
            if (!error){
                big_decimal_to_decimal(tmp, result);
                if (is_minus(value_1))
                    set_minus(result);
            }
            else
                res = is_minus(value_1) ? TOO_SMALL : TOO_LARGE;
        }
    }
    return res;
}
