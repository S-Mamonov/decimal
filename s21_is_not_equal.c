#include "s21_decimal.h"

int s21_is_not_equal(s21_decimal val1, s21_decimal val2){
    return !s21_is_equal(val1, val2);
}
