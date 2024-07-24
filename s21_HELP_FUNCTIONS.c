#include "s21_decimal.h"

void clear_s21_decimal(s21_decimal *val){
    for (int i = 0; i < 4; i++)
        val->bits[i] = 0;
}

int is_zerro(s21_decimal value){
    int res = value.bits[2] || value.bits[1] || value.bits[0];

    return res == 0;
}

int is_minus(s21_decimal value){
    return value.bits[3] & MINUS;
}

void set_minus(s21_decimal* value){
    value->bits[3] |= MINUS;
}

void set_plus(s21_decimal* value){
    value->bits[3] &= ~MINUS;
}

void decimal_to_big_decimal(s21_decimal value, big_decimal *res){
    for (int i = 0; i < 7; i++){
        if (i < 3){
            res->bits[i] = value.bits[i];
        }
        else
            res->bits[i] = 0;
    }
    res->scale = (value.bits[3] & SC) >> 16;
}

int getoverflow(big_decimal *value){
    uint32_t overflow = 0;

    for (int i = 0; i < 7; i++){
        value->bits[i] += overflow;
        overflow = value->bits[i] >> 32;
        value->bits[i] &= MAX4BYTE;
    }
    return overflow; //если 0, то всё успешно, иначе мегапереполнение.
}

int scale_up(big_decimal *value){
    big_decimal tmp = *value;
    int res;

    for (int i = 0; i < 7; i++)
        tmp.bits[i] *= 10;

    res = getoverflow(&tmp);
    if (res == 0){
        *value = tmp;
        value->scale++;
    }
    return res; //если 0, то всё успешно, иначе мегапереполнение.
}

uint64_t scale_down(big_decimal *value){
    uint64_t reminder = 0;

    for (int i = 6; i > -1; i--){
        value->bits[i] += reminder << 32;
        reminder = value->bits[i] % 10;
        value->bits[i] /= 10;
    }
    value->scale--;

    return reminder; //возможно стоит добавить округление прямо в функции
}

void to_same_scale(big_decimal *val1, big_decimal *val2){
    int diff;

    if (val1->scale < val2->scale){
        diff = val2->scale - val1->scale;

        for (int i = 0; i < diff; i++)
            scale_up(val1);
    }
    else if (val1->scale > val2->scale){
        diff = val1->scale - val2->scale;

        for (int i = 0; i < diff; i++)
            scale_up(val2);
    }
}

int is_mantis_equal(s21_decimal val1, s21_decimal val2){
    int res = 0;
    big_decimal current_value_1 = {0};
    big_decimal current_value_2 = {0};

    decimal_to_big_decimal(val1, &current_value_1);
    decimal_to_big_decimal(val2, &current_value_2);

    to_same_scale(&current_value_1, &current_value_2);

    for (int i = 6; !res && i > -1; i--){
        if (current_value_1.bits[i] > current_value_2.bits[i]){
            res = 1;
        }
        else if (current_value_1.bits[i] < current_value_2.bits[i])
            res = -1;
    }
    return res;
}

int normalization(big_decimal *value){
    int ostatok;
    for (int i = 7; i > 2; i--)
        while(value->bits[i] && value->scale)
            ostatok = scale_down(value); // дописать
}
