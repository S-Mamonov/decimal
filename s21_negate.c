#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result){
    if (is_zerro(value)){
        if (is_minus(value))
            value.bits[3] ^= MINUS;
    }
    else{
        value.bits[3] ^= MINUS;
    }

    *result = value;

    return 0;
}
