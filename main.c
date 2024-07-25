#include <stdio.h>
#include <stdint.h>

#include "s21_decimal.h"

void show_decimal(s21_decimal val){
    for (int i = 3; i > -1; i--){
        for (int j = 31; j > -1; j--)
            printf("%d ", (val.bits[i] >> j) & 1);
        puts("");
    }
}

void show_big(big_decimal val){
    for (int i = 6; i > -1; i--){
        for (int j = 63; j > -1; j--)
            printf("%d", (val.bits[i] >> j) & 1);
        puts("");
    }
}

int main()
{
    s21_decimal test1 = {13, 0, 0, 7 << 16};
    s21_decimal test2 = {1300, 0, 0, 9 << 16};
//    s21_decimal test1 = {0xffffffff, 0, 0, 9 << 16};
//    s21_decimal test2 = {0xffffffff, 0, 0, 9 << 16};
set_minus(&test1);
    puts("is mantis equal?");
    printf("eq? = %d\n", is_mantis_equal(test1, test2));

    big_decimal xx;
    big_decimal yy;
//s21_from_int_to_decimal(-1300, &test2);
//test2.bits[3] = (9 << 16) | MINUS;
//s21_from_int_to_decimal(7, &test1);
//set_minus(&test1);
//set_minus(&test2);
    show_decimal(test1);
    puts("");
    show_decimal(test2);

    printf("IS GREATer or eq %d\n", s21_is_greater_or_equal(test1, test2));
    printf("IS LESS or eq %d\n", s21_is_less_or_equal(test1, test2));

    puts("BIG");
    big_decimal temp;// = {0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff};
    temp.scale = 28;
    decimal_to_big_decimal(test1, &temp);
    show_big(temp);
    printf("scale = %d\n", temp.scale);

    puts("add");
    s21_decimal rr = {0};

    s21_add(test1, test2, &rr);
    show_decimal(rr);
    printf("scale = %d\n", rr.bits[3] >> 16);
    printf("rr = %d\n", rr.bits[0]);
//    decimal_to_big_decimal(test1, &xx);
//    decimal_to_big_decimal(test2, &yy);
//
//    show_big(xx);
//    printf("scale = %d\n", xx.scale);
//
//    show_big(yy);
//    printf("scale = %d\n", yy.scale);
//
//    puts("to_same_scale");
//
//    to_same_scale(&xx, &yy);
//
//    show_big(xx);
//    printf("scale = %d\n", xx.scale);
//
//    show_big(yy);
//    printf("scale = %d\n", yy.scale);
//    printf("yy = %d\n", yy.bits[0]);


    return 0;
}
