#include "s21_SmartCalc.h"

int setFirstPriority(char *str, Stack *stack, int i, int *minusSign,
                     int *plusSign) {
  int status = OK;

  if (str[i] == '+') {
    if (i == 0 || str[i - 1] == '(') {
      *plusSign = 1;
    } else {
      Lexeme tmp = {'+', PLUS, 1};
      status = push(stack, tmp);
    }
  } else if (str[i] == '-') {
    if (i == 0 || str[i - 1] == '(') {
      Lexeme tmp = {0, NUM, 0};
      status = push(stack, tmp);

      tmp.value = '-';
      tmp.type = MINUS;
      tmp.priority = 1;
      status = push(stack, tmp);

      *minusSign = 0;
    } else {
      Lexeme tmp = {'-', MINUS, 1};
      status = push(stack, tmp);
    }
  }

  return status;
}

int setSecondPriority(char *str, Stack *stack, int *i) {
  int status = OK;

  if (str[*i] == '*') {
    Lexeme tmp = {'*', MUL, 2};
    status = push(stack, tmp);
  } else if (str[*i] == '/') {
    Lexeme tmp = {'/', DIV, 2};
    status = push(stack, tmp);
  } else if (str[*i] == 'm') {
    Lexeme tmp = {'m', MOD, 2};
    status = push(stack, tmp);
    *i += 2;
  }

  return status;
}

int setThirdPriority(char *str, Stack *stack, int i) {
  int status = OK;

  if (str[i] == '^') {
    Lexeme tmp = {'^', EXP, 3};
    status = push(stack, tmp);
  }

  return status;
}

int setFourthPriority(char *str, Stack *stack, int *i) {
  int status = OK;

  if (str[*i] == 'c') {
    Lexeme tmp = {'c', COS, 4};
    status = push(stack, tmp);
    *i += 2;
  } else if (str[*i] == 't') {
    Lexeme tmp = {'t', TAN, 4};
    status = push(stack, tmp);
    *i += 2;
  } else if (str[*i] == 's') {
    if (str[*i + 1] == 'i') {
      Lexeme tmp = {'s', SIN, 4};
      status = push(stack, tmp);
      *i += 2;
    } else {
      Lexeme tmp = {'q', SQRT, 4};
      status = push(stack, tmp);
      *i += 3;
    }
  } else if (str[*i] == 'l') {
    if (str[*i + 1] == 'o') {
      Lexeme tmp = {'L', LOG, 4};
      status = push(stack, tmp);
      *i += 2;
    } else {
      Lexeme tmp = {'l', LN, 4};
      status = push(stack, tmp);
      *i += 1;
    }
  } else if (str[*i] == 'a') {
    if (str[*i + 1] == 's') {
      Lexeme tmp = {'S', ASIN, 4};
      status = push(stack, tmp);
    } else if (str[*i + 1] == 'c') {
      Lexeme tmp = {'C', ACOS, 4};
      status = push(stack, tmp);
    } else {
      Lexeme tmp = {0, ATAN, 4};
      status = push(stack, tmp);
    }
    *i += 3;
  }

  return status;
}

int setZeroPriority(char *str, Stack *stack, int i) {
  int status = OK;

  if (str[i] == '(') {
    Lexeme tmp = {'(', LEFT_BRACKET, 0};
    status = push(stack, tmp);
  } else if (str[i] == ')') {
    Lexeme tmp = {')', RIGHT_BRACKET, 0};
    status = push(stack, tmp);
  } else if (str[i] == 'x') {
    Lexeme tmp = {'x', X, 0};
    status = push(stack, tmp);
  }

  return status;
}