#include <stdlib.h>
#include <string.h>

#include "smartcalc.h"

int parse_str(char *str, Stack_t *stack) {
  char str_number[256] = {0};
  int result_code = 0;
  int num_pos = 0;
  int point_cnt = 0;
  double value = 0;
  for (; *str; str++) {
    if (strchr("0123456789.", *str)) {
      while (strchr("0123456789.", *str) && *str) {
        if (*str == '.') point_cnt++;
        str_number[num_pos] = *str;
        num_pos++;
        str++;
      }
      if (point_cnt > 1) result_code = 1;
      str--;
      value = atof(str_number);
      pushback(stack, value, 0, _number);
      for (int i = 0; i <= num_pos; i++) str_number[i] = 0;
      num_pos = 0;
      point_cnt = 0;
    } else if (*str == 'x') {
      pushback(stack, 0, 0, _x);
    } else if (*str == '+') {
      if (stack->head->type == _o_parenth) pushback(stack, 0, 0, _number);
      pushback(stack, 0, 1, _plus);
    } else if (*str == '-') {
      if (stack->head->type == _o_parenth) pushback(stack, 0, 0, _number);
      pushback(stack, 0, 1, _minus);
    } else if (*str == '*') {
      pushback(stack, 0, 2, _mult);
    } else if (*str == '/') {
      pushback(stack, 0, 2, _div);
    } else if (*str == 'm') {
      pushback(stack, 0, 2, _mod);
      str += 2;
    } else if (*str == '^') {
      pushback(stack, 0, 3, _power);
    } else if (*str == 'c') {
      pushback(stack, 0, 4, _cos);
      str += 2;
    } else if (*str == 't') {
      pushback(stack, 0, 4, _tan);
      str += 2;
    } else if (*str == 's') {
      str++;
      if (*str == 'i') {
        pushback(stack, 0, 4, _sin);
        str++;
      } else if (*str == 'q') {
        pushback(stack, 0, 4, _sqrt);
        str += 2;
      }
    } else if (*str == 'l') {
      str++;
      if (*str == 'n') {
        pushback(stack, 0, 4, _ln);
      } else if (*str == 'o') {
        pushback(stack, 0, 4, _log);
        str++;
      }
    } else if (*str == 'a') {
      str++;
      if (*str == 'c') {
        pushback(stack, 0, 4, _acos);
        str += 2;
      } else if (*str == 's') {
        pushback(stack, 0, 4, _asin);
        str += 2;
      } else if (*str == 't') {
        pushback(stack, 0, 4, _atan);
        str += 2;
      }
    } else if (*str == '(') {
      pushback(stack, 0, -1, _o_parenth);
    } else if (*str == ')') {
      pushback(stack, 0, -1, _c_parenth);
    }
  }
  return result_code;
}