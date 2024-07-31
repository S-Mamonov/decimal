#include "s21_decimal.h"

void clear_s21_decimal(s21_decimal *val){
    s21_decimal tmp = {0};
    *val = tmp;
}

int is_zero(s21_decimal value){
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
    big_decimal tmp = {0};

    for (int i = 0; i < 3; i++)
        tmp.bits[i] = value.bits[i] & MAX4BYTE;

    tmp.scale = (value.bits[3] & SC) >> 16;

    *res = tmp;
}

void big_decimal_to_decimal(big_decimal value, s21_decimal *res){
    for (int i = 0; i < 3; i++)
        res->bits[i] = value.bits[i];
    res->bits[3] = value.scale << 16;
}

int getoverflow(big_decimal *value){
    uint32_t overflow = 0;

    for (int i = 0; i < 7; i++){
        value->bits[i] += overflow;
        overflow = value->bits[i] >> 32;
        value->bits[i] &= MAX4BYTE;
    }
    return overflow; //if 0, it's ok, else mega overflow.
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
    return res; //if 0, it's ok, else mega overflow.
}

uint64_t scale_down(big_decimal *value){
    uint64_t remainder = 0;

    for (int i = 6; i > -1; i--){
        value->bits[i] += remainder << 32;
        remainder = value->bits[i] % 10;
        value->bits[i] /= 10;
    }
    value->scale--;

    return remainder;
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

int add_mantis(s21_decimal val1, s21_decimal val2, big_decimal *res){
    big_decimal big_val1, big_val2;

    decimal_to_big_decimal(val1, &big_val1);
    decimal_to_big_decimal(val2, &big_val2);

    to_same_scale(&big_val1, &big_val2);

    res->scale = big_val1.scale;
    for (int i = 0; i < 7; i++)
        res->bits[i] = big_val1.bits[i] + big_val2.bits[i];

    return getoverflow(res);
}

int normalize(big_decimal *value){
    int remainder, error = 0, cnt = 0;

    for (int i = 6; i > 2; i--)
        while((value->bits[i] && value->scale) || value->scale > 28){
            remainder = scale_down(value);

            if (remainder)
                cnt++;
        }

    if(value->scale == 0)
        for (int i = 6; !error, i > 2; i--)
            if (value->bits[i])
                error = 1;

    if (!error && remainder > 5){
        value->bits[0] += 1;
        getoverflow(value);
        if(value->bits[3]){
            if (value->scale){ //to another foonc
                remainder = scale_down(value);
                if (remainder > 5)
                    value->bits[0] += 1;
                else if (remainder == 5)
                    if(value->bits[0] & 1)
                        value->bits[0] += 1;
            }
            else
                error = 1;
        }
    }
    else if (!error && remainder == 5){
        if (cnt > 1)
            value->bits[0] += 1;
        else if (value->bits[0] & 1)
            value->bits[0] += 1;
    }
    return error;
}
