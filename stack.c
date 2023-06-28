#include <stdlib.h>

#include "smartcalc.h"

void pushback(Stack_t *stack, double value, int priority, type_t type) {
  Node_t *tmp = malloc(sizeof(Node_t));
  if (tmp) {
    tmp->value = value;
    tmp->priority = priority;
    tmp->type = type;
    tmp->prev = NULL;
    tmp->next = stack->head;
    if (stack->head) (stack->head)->prev = tmp;
    stack->head = tmp;
    if (!stack->tail) (stack->tail) = tmp;
  }
}

Node_t *popback(Stack_t *stack) {
  Node_t *popped = stack->head;
  stack->head = (stack->head)->next;
  if (stack->head)
    stack->head->prev = NULL;
  else
    stack->tail = NULL;
  return popped;
}

Node_t *popfront(Stack_t *stack) {
  Node_t *popped = stack->tail;
  stack->tail = (stack->tail)->prev;
  if (stack->tail)
    stack->tail->next = NULL;
  else
    stack->head = NULL;
  return popped;
}

int is_empty(Stack_t *stack) {
  return stack->tail == NULL && stack->head == NULL ? 1 : 0;
}

type_t show_top_node_type(Stack_t *stack) { return stack->head->type; }

int show_top_node_priority(Stack_t *stack) { return stack->head->priority; }
