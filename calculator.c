#include <math.h>
#include <stdlib.h>

#include "smartcalc.h"

double calculate(Stack_t *inputStack) {
  Stack_t supportStack = {NULL, NULL};
  Node_t *tmp = NULL;
  Node_t *a = NULL;
  Node_t *b = NULL;
  double result = 0;
  while (!is_empty(inputStack)) {
    tmp = popfront(inputStack);
    if (tmp->type <= _number)
      pushback(&supportStack, tmp->value, tmp->priority, tmp->type);
    else if (tmp->type >= _plus && tmp->type <= _power) {
      a = popback(&supportStack);
      b = popback(&supportStack);
      if (tmp->type == _plus) {
        pushback(&supportStack, a->value + b->value, 0, 0);
      } else if (tmp->type == _minus) {
        pushback(&supportStack, b->value - a->value, 0, 0);
      } else if (tmp->type == _mult) {
        pushback(&supportStack, a->value * b->value, 0, 0);
      } else if (tmp->type == _div) {
        pushback(&supportStack, b->value / a->value, 0, 0);
      } else if (tmp->type == _mod) {
        pushback(&supportStack, fmod(b->value, a->value), 0, 0);
      } else if (tmp->type == _power) {
        pushback(&supportStack, pow(b->value, a->value), 0, 0);
      }
      free(a);
      free(b);
    } else if (tmp->type >= _cos) {
      a = popback(&supportStack);
      if (tmp->type == _cos) {
        pushback(&supportStack, cos(a->value), 0, 0);
      } else if (tmp->type == _sin) {
        pushback(&supportStack, sin(a->value), 0, 0);
      } else if (tmp->type == _tan) {
        pushback(&supportStack, tan(a->value), 0, 0);
      } else if (tmp->type == _acos) {
        pushback(&supportStack, acos(a->value), 0, 0);
      } else if (tmp->type == _asin) {
        pushback(&supportStack, asin(a->value), 0, 0);
      } else if (tmp->type == _atan) {
        pushback(&supportStack, atan(a->value), 0, 0);
      } else if (tmp->type == _sqrt) {
        pushback(&supportStack, sqrt(a->value), 0, 0);
      } else if (tmp->type == _ln) {
        pushback(&supportStack, log(a->value), 0, 0);
      } else if (tmp->type == _log) {
        pushback(&supportStack, log10(a->value), 0, 0);
      }
      free(a);
    }
    free(tmp);
  }
  tmp = popfront(&supportStack);
  result = tmp->value;
  free(tmp);
  return result;
}