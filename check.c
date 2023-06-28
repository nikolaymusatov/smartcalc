#include <stdio.h>
#include <string.h>

#include "smartcalc.h"

int input_data(char* str) {
  int status = 0;
  fgets(str, 260, stdin);
  int len = strlen(str);
  if (len > 256) status = 1;
  str[len - 1] = '\0';
  return status;
}

int check_data(char* str) {
  int status = 0;
  int open_parenthesis_qnt = 0;
  int closed_parenthesis_qnt = 0;
  char prev_symbol = '$';
  for (; *str; str++) {
    if (!strchr("alstcm().0123456789x+-*/^", *str))
      status = 1;
    else if (strchr("*/^", *str) && !strchr(")0123456789x", prev_symbol))
      status = 1;
    else if (strchr("+-", *str) && !strchr("$()0123456789x", prev_symbol))
      status = 1;
    else if (*str == '.' && !strchr("0123456789", prev_symbol))
      status = 1;
    else if (prev_symbol == '.' && !strchr("0123456789", *str))
      status = 1;
    else if (*str == 'm')
      str = check_mod(&status, str, prev_symbol);
    else if (*str == 'c')
      str = check_cos(&status, &open_parenthesis_qnt, str, prev_symbol);
    else if (*str == 't')
      str = check_tan(&status, &open_parenthesis_qnt, str, prev_symbol);
    else if (*str == 's')
      str = check_sin_sqrt(&status, &open_parenthesis_qnt, str, prev_symbol, 0);
    else if (*str == 'l')
      str = check_ln_log(&status, &open_parenthesis_qnt, str, prev_symbol);
    else if (*str == 'a')
      str = check_arc(&status, &open_parenthesis_qnt, str, prev_symbol);
    else if (*str == '(') {
      open_parenthesis_qnt++;
      if (!strchr("$d(+-*/^", prev_symbol)) status = 1;
    } else if (*str == ')') {
      closed_parenthesis_qnt++;
      if (!strchr(")0123456789x", prev_symbol)) status = 1;
      if (closed_parenthesis_qnt > open_parenthesis_qnt) status = 1;
    }
    if (status) break;
    prev_symbol = *str;
  }
  if (strchr("+-*/^.", prev_symbol)) status = 1;
  if (open_parenthesis_qnt != closed_parenthesis_qnt) status = 1;
  return status;
}

char* check_mod(int* status, char* str, char prev_symbol) {
  if (!strchr(")0123456789x", prev_symbol))
    *status = 1;
  else {
    for (char* mod = "mod"; *mod; str++, mod++)
      if (*mod != *str) *status = 1;
    str--;
  }
  return str;
}

char* check_cos(int* status, int* open_parenthesis_qnt, char* str,
                char prev_symbol) {
  if (!strchr("$(+-*/^", prev_symbol))
    *status = 1;
  else {
    for (char* cos = "cos("; *cos; str++, cos++)
      if (*cos != *str) *status = 1;
    if (!*status) (*open_parenthesis_qnt)++;
    str--;
  }
  return str;
}

char* check_tan(int* status, int* open_parenthesis_qnt, char* str,
                char prev_symbol) {
  if (!strchr("$(+-*/^", prev_symbol))
    *status = 1;
  else {
    for (char* tan = "tan("; *tan; str++, tan++)
      if (*tan != *str) *status = 1;
    if (!*status) (*open_parenthesis_qnt)++;
    str--;
  }
  return str;
}

char* check_sin_sqrt(int* status, int* open_parenthesis_qnt, char* str,
                     char prev_symbol, int arc) {
  if (!strchr("$(+-*/^", prev_symbol))
    *status = 1;
  else {
    str++;
    if (*str == 'i') {
      for (char* sin = "in("; *sin; str++, sin++)
        if (*sin != *str) *status = 1;
    } else if (*str == 'q' && !arc) {
      for (char* sqrt = "qrt("; *sqrt; str++, sqrt++)
        if (*sqrt != *str) *status = 1;
    } else
      *status = 1;
    if (!*status) (*open_parenthesis_qnt)++;
    str--;
  }
  return str;
}

char* check_ln_log(int* status, int* open_parenthesis_qnt, char* str,
                   char prev_symbol) {
  if (!strchr("$(+-*/^", prev_symbol))
    *status = 1;
  else {
    str++;
    if (*str == 'n') {
      for (char* ln = "n("; *ln; str++, ln++)
        if (*ln != *str) *status = 1;
    } else if (*str == 'o') {
      for (char* log = "og("; *log; str++, log++)
        if (*log != *str) *status = 1;
    } else
      *status = 1;
    if (!*status) (*open_parenthesis_qnt)++;
    str--;
  }
  return str;
}

char* check_arc(int* status, int* open_parenthesis_qnt, char* str,
                char prev_symbol) {
  str++;
  if (*str == 'c') {
    str = check_cos(status, open_parenthesis_qnt, str, prev_symbol);
  } else if (*str == 's') {
    str = check_sin_sqrt(status, open_parenthesis_qnt, str, prev_symbol, 1);
  } else if (*str == 't') {
    str = check_tan(status, open_parenthesis_qnt, str, prev_symbol);
  } else
    *status = 1;
  return str;
}
