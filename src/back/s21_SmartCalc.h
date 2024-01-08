#ifndef S21_SMART_CALC_H
#define S21_SMART_CALC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define CALC_ERROR 1
#define MEM_ERROR 2
#define INCORRECT_INPUT 3
#define NAN_RES 4
#define INF_RES 5

typedef struct Lexeme {
  double value;
  int type;
  int priority;
} Lexeme;

typedef enum LexemeType {
  NUM,
  X,
  LEFT_BRACKET,
  RIGHT_BRACKET,
  PLUS,
  MINUS,
  MUL,
  DIV,
  EXP,
  MOD,
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG
} LexemeType;

typedef struct Node {
  Lexeme lexeme;
  struct Node *next;
} Node;

typedef struct Stack {
  Node *top;
} Stack;

// Stack
void initStack(Stack *stack);
int push(Stack *stack, Lexeme addLexeme);
double pop(Stack *stack);

// parser
int parseStr(char *str);
int parseBrackets(char *str);
int parseBracketPosition(char *str);
int parseOtherFuncs(char *str);
int parseDots(char *str);
int parseOperators(char *str);
int parseTrig(char *str);
int parseX(char *str);
int parseToStack(char *str, Stack *stack);

// set priority
int setZeroPriority(char *str, Stack *stack, int i);
int setFirstPriority(char *str, Stack *stack, int i, int *minusSign,
                     int *plusSign);
int setSecondPriority(char *str, Stack *stack, int *i);
int setThirdPriority(char *str, Stack *stack, int i);
int setFourthPriority(char *str, Stack *stack, int *i);

int getNumber(char *str, Stack *stack, int *i, int *unaryMinus, int *unaryPlus);
int reverseStack(Stack *inputStack, Stack *reversedStack);
int getPostfix(Stack *infix, Stack *buffer, Stack *postfix);

int calculateResult(Stack *rpn, double x, double *result);
double calculateTrig(Lexeme *operation, Lexeme *number);
double calculateSimpleOperation(Lexeme *operation, double firstNumber,
                                double secondNumber);

// calc
int from_answer(char *str, double *result, double x);

#ifdef __cplusplus
}
#endif

#endif  // S21_SMART_CALC_H