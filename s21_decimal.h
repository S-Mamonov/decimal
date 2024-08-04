#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <stdint.h>
#include <math.h>

#define MINUS 0x80000000
#define SC 0x00ff0000
#define MAX4BYTE 0xffffffff

typedef struct {
    int bits[4];
} s21_decimal;

typedef struct {
    uint64_t bits[7];
    uint8_t scale;
} big_decimal;

typedef enum {
  ARITHMETIC_OK,
  TOO_LARGE,
  TOO_SMALL,
  DIVISION_BY_ZERO
} arithmetic_result;

//int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) 75
//int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) 88
//int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) 55
//int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) 90

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
//int s21_from_float_to_decimal(float src, s21_decimal *dst)		39
int s21_from_decimal_to_int(s21_decimal src, int *dst);
//int s21_from_decimal_to_float(s21_decimal src, float *dst)		12

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

//help functions
int is_zero(s21_decimal value);
int is_minus(s21_decimal value);
void set_minus(s21_decimal* value);
void set_plus(s21_decimal* value);
void decimal_to_big_decimal(s21_decimal value, big_decimal *res);
int getoverflow(big_decimal *value);
int scale_up(big_decimal *value);
uint64_t scale_down(big_decimal *value);
void to_same_scale(big_decimal *val1, big_decimal *val2);
int is_mantis_equal(s21_decimal val1, s21_decimal val2);

#endif // S21_DECIMAL_H_INCLUDED
