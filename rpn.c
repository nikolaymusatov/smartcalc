#include <stdlib.h>

#include "smartcalc.h"

Stack_t convert_to_rpn(Stack_t *inputStack) {
  Stack_t readyStack = {NULL, NULL}, supportStack = {NULL, NULL};
  Node_t *node = NULL;
  Node_t *tmp = NULL;
  while (!is_empty(inputStack)) {
    node = popfront(inputStack);
    if (node->type <= _number) {
      pushback(&readyStack, node->value, node->priority, node->type);
    } else if (node->type >= _plus && node->type <= _log) {
      while (!is_empty(&supportStack) &&
             node->priority <= show_top_node_priority(&supportStack)) {
        tmp = popback(&supportStack);
        pushback(&readyStack, tmp->value, tmp->priority, tmp->type);
        free(tmp);
      }
      pushback(&supportStack, node->value, node->priority, node->type);
    } else if (node->type == _o_parenth) {
      pushback(&supportStack, node->value, node->priority, node->type);
    } else if (node->type == _c_parenth) {
      while (show_top_node_type(&supportStack) != _o_parenth) {
        tmp = popback(&supportStack);
        pushback(&readyStack, tmp->value, tmp->priority, tmp->type);
        free(tmp);
      }
      free(popback(&supportStack));
    }
    free(node);
  }
  while (!is_empty(&supportStack)) {
    node = popback(&supportStack);
    pushback(&readyStack, node->value, node->priority, node->type);
    free(node);
  }
  node = NULL;
  tmp = NULL;
  return readyStack;
}