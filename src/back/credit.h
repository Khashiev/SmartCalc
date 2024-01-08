#ifndef S21_CREDIT_H
#define S21_CREDIT_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define is_nan(x) __builtin_isnan(x)
#define is_inf(x) __builtin_isinf(x)

#define YEAR 365
#define MONTHS_YEAR 12
#define MAX_EXPR_LEN 2048
#define MAX_NUM_PARAMS 1
#define MIN_NUM_PARAMS 0
#define MAX_DIGIT 255
#define MAX_STACK_SIZE 2048

enum Months {
  December,
  January,
  February,
  March,
  April,
  May,
  June,
  July,
  August,
  September,
  October,
  November
};

void credit_evualete_ann(double percents, double month, double sum,
                         double *percents_result, double *result,
                         double *montly_pay);

int credit_evualete_diff(double percents, double month, double sum,
                         double *percents_result, double *result,
                         double *montly_pay);

#endif  // S21_CREDIT_H