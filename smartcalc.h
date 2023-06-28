#ifndef SRC_SMARTCALC_H_
#define SRC_SMARTCALC_H_
#define SUCCESS 0
#define WRONG_EXPRESSION 1
#define BUFFER_OVERFLOW 2
#define STACK_OVERFLOW 100
#define STACK_UNDERFLOW 101

/*---PARSER FUNCTIONS---*/
typedef enum {
  _x,
  _number,
  _plus,
  _minus,
  _mult,
  _div,
  _mod,
  _power,
  _cos,
  _sin,
  _tan,
  _acos,
  _asin,
  _atan,
  _sqrt,
  _ln,
  _log,
  _o_parenth,
  _c_parenth
} type_t;

typedef struct Node_t {
  double value;
  int priority;
  type_t type;
  struct Node_t* next;
  struct Node_t* prev;
} Node_t;

typedef struct Stack {
  Node_t* head;
  Node_t* tail;
} Stack_t;

void pushback(Stack_t* stack, double value, int priority, type_t type);
void pushfront(Stack_t* stack, double value, int priority, type_t type);
Node_t* popback(Stack_t* stack);
Node_t* popfront(Stack_t* stack);
int is_empty(Stack_t* stack);
type_t show_top_node_type(Stack_t* stack);
int show_top_node_priority(Stack_t* stack);
void print_values_from_head(Stack_t* stack);
void print_values_from_tail(Stack_t* stack);
int parse_str(char* str, Stack_t* stack);

/*---CHECK FUNCTIONS---*/
int input_data(char* str);
int check_data(char* str);
char* check_mod(int* status, char* str, char prev_symbol);
char* check_cos(int* status, int* open_parenthesis_qnt, char* str,
                char prev_symbol);
char* check_tan(int* status, int* open_parenthesis_qnt, char* str,
                char prev_symbol);
char* check_sin_sqrt(int* status, int* open_parenthesis_qnt, char* str,
                     char prev_symbol, int arc);
char* check_ln_log(int* status, int* open_parenthesis_qnt, char* str,
                   char prev_symbol);
char* check_arc(int* status, int* open_parenthesis_qnt, char* str,
                char prev_symbol);

/*---RPN FUNCTIONS---*/
Stack_t convert_to_rpn(Stack_t* inputStack);

/*---CALCULATION FUNCTIONS---*/
double calculate(Stack_t* stack);

#endif  // SRC_SMARTCALC_H_
