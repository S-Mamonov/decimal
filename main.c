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
//    s21_decimal test1 = {12, 15, 0, 1 << 16};
//    s21_decimal test2 = {1302, 0, 0, 9 << 16};
//    s21_decimal rez = {1302, 0, 0, 9 << 16};

    s21_decimal test1 = {0xffffffff, 0xffffffff, 0xffffffff, 9 << 16};
    s21_decimal test2 = {0xffffffff, 0xffffffff, 0xffffffff, 9 << 16};
    s21_decimal test3 = {0, 0, 0, 2 << 16};
//set_minus(&test1);

    big_decimal xx;
    big_decimal yy;

    show_decimal(test1);
    puts("");
    show_decimal(test2);



    puts("BIG");
    big_decimal temp;// = {0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff};
    temp.scale = 28;
    decimal_to_big_decimal(test1, &temp);
    show_big(temp);
    printf("scale = %d\n", temp.scale);
    temp.bits[0]++;
    puts("BIG+1");
    show_big(temp);
    printf("scale = %d\n", temp.scale);

    getoverflow(&temp);
    puts("get OF BIG");
    show_big(temp);
    printf("scale = %d\n", temp.scale);

    normalize(&temp);
    puts("NORMAL BIG");
    show_big(temp);
    printf("scale = %d\n", temp.scale);

    puts("add");
    s21_decimal rr = {0};

    s21_add(test1, test2, &rr);
    show_decimal(rr);
    printf("scale = %d\n", (rr.bits[3] & SC) >> 16);
    printf("rr = %d\n", rr.bits[0]);

    set_minus(&test3);
    s21_floor(test3, &test1);
    show_decimal(test3);
    puts("----");
    show_decimal(test1);


    return 0;
}
