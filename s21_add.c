#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){
    int res = 0;
    int error = 0;

    if (is_zero(value_1) && is_zero(value_2)){
        clear_s21_decimal(result);
    }
    else if (is_zero(value_1) && !is_zero(value_2)){
        *result = value_2;
    }
    else if (!is_zero(value_1) && is_zero(value_2)){
        *result = value_1;
    }
    else{
        big_decimal current_value_1;
        big_decimal current_value_2;
        big_decimal big_res = {0};

        decimal_to_big_decimal(value_1, &current_value_1);
        decimal_to_big_decimal(value_2, &current_value_2);
        to_same_scale(&current_value_1, &current_value_2);

        if (!is_minus(value_1) && !is_minus(value_2)){
            for (int i = 0; i < 7; i++){
                big_res.bits[i] = current_value_1.bits[i] + current_value_2.bits[i];
                big_res.scale = current_value_1.scale;
            }
            error = getoverflow(&big_res);

//            if (!error)
//                error = normalization(&big_res);
            if (!error)
                big_decimal_to_decimal(big_res, result);
        }
    }

    return res;
}
