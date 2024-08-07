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
    s21_decimal test1 = {1300, 1300, 0, 9 << 16};
    s21_decimal test2 = {1303, 1200, 0, 9 << 16};
    s21_decimal rez = {0b01111111111111111111111111111111, 0, 0, 0 << 16};

//    s21_decimal test1 = {0x00ffffff, 0xffffffff, 0xffffffff, 9 << 16};
//    s21_decimal test2 = {0xffffffff, 0xffffffff, 0xffffffff, 9 << 16};
    s21_decimal test3 = {0, 0, 0, 2 << 16};
//set_minus(&test1);
//set_minus(&test2);
//puts("IS GREATER");
//int gr = s21_is_greater(test1, test2);
//printf("greater = %d\n", gr);
show_decimal(test1);
puts("");
show_decimal(test2);
s21_add(test1, test2, &rez);
puts("TESTING ADD");
show_decimal(rez);
printf("%u\n", rez.bits[0]);
puts("END TESTING ADD");

float qqq;
int qaz;
s21_from_decimal_to_float(rez, &qqq);
printf("FLOAT = %f\n", qqq);
s21_from_decimal_to_int(rez, &qaz);
printf("dec2int = %d\n", qaz);

s21_decimal qwe = {2147483648, 0, 0, 0 << 16};
int ww = -11;
set_minus(&qwe);
s21_from_decimal_to_int(qwe, &ww);
printf("dec2int = %d\n", ww);
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
