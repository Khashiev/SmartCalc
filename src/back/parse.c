#include "s21_SmartCalc.h"

int parseStr(char *str) {
  int status = OK;

  if (strlen(str) < 1 || strlen(str) > 255) {
    status = INCORRECT_INPUT;
  }

  if (status == OK) {
    if (parseBrackets(str)) {
      status = INCORRECT_INPUT;
    } else if (parseDots(str)) {
      status = INCORRECT_INPUT;
    } else if (parseOperators(str)) {
      status = INCORRECT_INPUT;
    } else if (parseTrig(str)) {
      status = INCORRECT_INPUT;
    } else if (parseOtherFuncs(str)) {
      status = INCORRECT_INPUT;
    } else if (parseX(str)) {
      status = INCORRECT_INPUT;
    }
  }

  return status;
}

int parseBrackets(char *str) {
  int status = OK;
  int leftBracket = 0;
  int rightBracket = 0;

  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == '(') {
      leftBracket++;

      if (str[i + 1] == ')') {
        status = INCORRECT_INPUT;
      }
    }

    if (str[i] == ')') {
      rightBracket++;

      if (leftBracket < rightBracket) {
        status = INCORRECT_INPUT;
      }
    }
  }

  if (leftBracket != rightBracket) {
    status = INCORRECT_INPUT;
  }

  if (status == OK) {
    parseBracketPosition(str);
  }

  return status;
}

int parseBracketPosition(char *str) {
  int status = OK;
  int len = strlen(str);

  for (int i = 0; str[i] != '\0'; i++) {
    if (i == 0 && str[i] == ')') {
      status = INCORRECT_INPUT;
    }

    if (i == len - 1 && str[i] == '(') {
      status = INCORRECT_INPUT;
    }

    if (str[i] == '(' && i != 0) {
      if (str[i - 1] == ')' || isdigit(str[i - i])) {
        status = INCORRECT_INPUT;
      }
    }

    if (str[i] == ')' && i != 0) {
      if (str[i + 1] == '(' || isdigit(str[i + i])) {
        status = INCORRECT_INPUT;
      }
    }
  }

  return status;
}

int parseDots(char *str) {
  int status = OK;
  char *ptr = str;

  while (*ptr != '\0' && status == OK) {
    int dots = 0;

    if (isdigit(*ptr) || *ptr == '.') {
      while (isdigit(*ptr) || *ptr == '.') {
        if (*ptr == '.') {
          dots++;

          if (!isdigit(*(ptr - 1))) {
            status = INCORRECT_INPUT;
          }
        }
        ptr++;
      }
      ptr--;
    }

    if (dots > 1) {
      status = INCORRECT_INPUT;
    }

    ptr++;
  }

  return status;
}

int parseOperators(char *str) {
  int status = OK;
  int len = strlen(str);

  for (int i = 0; i < len && status == OK; i++) {
    if (strchr("+-", str[i])) {
      if (i == len - 1) {
        status = INCORRECT_INPUT;
      }

      if (i != 0 && i != len - 1) {
        if (i > 0 &&
            (strchr(")/*^", str[i + 1]) || strchr("/*^+-", str[i - 1]))) {
          status = INCORRECT_INPUT;
        }
      }
    }

    if (strchr("/*^", str[i])) {
      if (i == 0 || i == len - 1) {
        status = INCORRECT_INPUT;
      }

      if (i != 0 && i != len - 1) {
        if (i > 0 &&
            (strchr(")/*^", str[i + 1]) || strchr("/*^+-", str[i - 1]))) {
          status = INCORRECT_INPUT;
        }
      }
    }

    if (str[i] == 'm') {
      if (i == 0 || i > len - 4) {
        status = INCORRECT_INPUT;
      }

      if (i != 0 || i < len - 4) {
        if (i > 0 && !isdigit(str[i - 1]) && strchr(")x", str[i - 1]) == NULL) {
          status = INCORRECT_INPUT;
        }

        if (i > 0 && !isdigit(str[i + 3]) && strchr("(x", str[i + 3]) == NULL) {
          status = INCORRECT_INPUT;
        }
      }
      i += 2;
    }
  }

  return status;
}

int parseTrig(char *str) {
  int status = OK;
  int len = strlen(str);

  for (int i = 0; i < len && status == OK; i++) {
    if (str[i] == 'c' || (str[i] == 't' && str[i - 1] != 'r') ||
        (str[i] == 's' && str[i + 1] == 'i')) {
      if (i > len - 6) {
        status = INCORRECT_INPUT;
      }

      if (i != 0 || i < len - 6) {
        if (i > 0 && (strchr(")x", str[i - 1]) || isdigit(str[i - 1]))) {
          status = INCORRECT_INPUT;
        }
      }
      i += 2;
    }

    if (str[i] == 'a') {
      if (i > len - 7) {
        status = INCORRECT_INPUT;
      }

      if (i != 0 || i < len - 7) {
        if (i > 0 && (strchr(")x", str[i - 1]) || isdigit(str[i - 1]))) {
          status = INCORRECT_INPUT;
        }
      }
      i += 3;
    }
  }

  return status;
}

int parseOtherFuncs(char *str) {
  int status = OK;
  int len = strlen(str);

  for (int i = 0; i < len && status == OK; i++) {
    if (str[i] == 'l' && str[i + 1] == 'n') {
      if (i > len - 5) {
        status = INCORRECT_INPUT;
      }

      if (i != 0 || i < len - 5) {
        if (i > 0 && (strchr(")x", str[i - 1]) || isdigit(str[i - 1]))) {
          status = INCORRECT_INPUT;
        }
      }
      i++;
    }

    if (str[i] == 's' && str[i + 1] == 'q') {
      if (i > len - 6) {
        status = INCORRECT_INPUT;
      }

      if (i != 0 || i < len - 7) {
        if (i > 0 && (strchr(")x", str[i - 1]) || isdigit(str[i - 1]))) {
          status = INCORRECT_INPUT;
        }
      }

      if (str[i + 5] == '-') {
        status = INCORRECT_INPUT;
      }
      i += 3;
    }

    if (str[i] == 'l' && str[i + 1] == 'o') {
      if (i > len - 6) {
        status = INCORRECT_INPUT;
      }
      i += 2;
    }
  }

  return status;
}

int parseX(char *str) {
  int status = OK;
  int len = strlen(str);

  for (int i = 0; i < len && status == OK; i++) {
    if (str[i] == 'x' && len != 1) {
      if (i == 0 && (strchr(")x", str[i + 1]) || isdigit(str[i + 1]))) {
        status = INCORRECT_INPUT;
      }

      if (i == len - 1 && (strchr(")x", str[i - 1]) || isdigit(str[i - 1]))) {
        status = INCORRECT_INPUT;
      }

      if (i > 0 && i < len - 1 &&
          (str[i + 1] == '(' || str[i + 1] == 'x' || isdigit(str[i + 1]))) {
        status = INCORRECT_INPUT;
      }

      if (i > 0 && i < len - 1 &&
          (str[i - 1] == ')' || str[i - 1] == 'x' || isdigit(str[i - 1]))) {
        status = INCORRECT_INPUT;
      }
    }
  }

  return status;
}