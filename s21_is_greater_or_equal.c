#include "s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal val1, s21_decimal val2){
    return s21_is_greater(val1, val2) || s21_is_equal(val1, val2);
}
