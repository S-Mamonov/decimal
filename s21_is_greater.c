#include "s21_decimal.h"

int s21_is_greater(s21_decimal val1, s21_decimal val2){
    int res;

    if (is_zero(val1)) set_plus(&val1);
    if (is_zero(val2)) set_plus(&val2);

    if (!is_minus(val1) && is_minus(val2)){
        res = 1;
    }
    else if (is_minus(val1) && !is_minus(val2)){
        res = 0;
    }
    else {
        if (!is_minus(val1)){
            res = is_mantis_equal(val1, val2) == 1 ? 1 : 0;
        }
        else{
            res = is_mantis_equal(val1, val2) == -1 ? 1 : 0;
        }
    }
    return res;
}
