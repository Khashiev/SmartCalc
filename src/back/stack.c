#include "s21_SmartCalc.h"

void initStack(Stack* stack) { stack->top = NULL; }

int push(Stack* stack, Lexeme addLexeme) {
  int status = OK;
  Node* newNode = malloc(sizeof(Node));

  if (newNode != NULL) {
    newNode->lexeme = addLexeme;
    newNode->next = stack->top;

    stack->top = newNode;
  } else {
    status = MEM_ERROR;
  }

  return status;
}

double pop(Stack* stack) {
  double res = 0;

  if (stack->top != NULL) {
    res = stack->top->lexeme.value;

    Node* tmp = stack->top;
    stack->top = stack->top->next;

    free(tmp);
  }

  return res;
}
