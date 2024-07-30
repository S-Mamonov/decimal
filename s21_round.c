#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result){
    clear_s21_decimal(result);
    int remainder = 0;
    int cnt = 0;
    big_decimal tmp;
    int scale = (value.bits[3] & SC) >> 16;;

    decimal_to_big_decimal(value, &tmp);

    for (int i = 0; i < scale; i++){
        remainder = scale_down(&tmp);
        if(remainder)
            cnt++;
    }
    //if ()

    return 0;
}
