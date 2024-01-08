#include <check.h>

#include "../back/credit.h"
#include "../back/s21_SmartCalc.h"

START_TEST(smartCalc_test_1) {
  double res = 0.0;
  char *str = "200*7-323+50/0.2+2*(123-112)";
  int error = 0;
  error = from_answer(str, &res, 0);
  ck_assert_int_eq(res, 1349);
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_2) {
  double res = 0.0;
  char *str = "sin(1)^2+cos(1)^2";
  int error = 0;
  error = from_answer(str, &res, 0);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_3) {
  double res = 0.0;
  char *str = "2^3^2";
  int error = 0;
  error = from_answer(str, &res, 0);
  ck_assert_int_eq(res, 512);
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_4) {
  double res = 0.0;
  char *str = "100-2^(2^3)";
  int error = 0;
  error = from_answer(str, &res, 0);
  ck_assert_int_eq(res, 100 - pow(2, pow(2, 3)));
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_5) {
  char *str = "(*)|(*))";
  int error = 0;
  double res = 0;
  error = from_answer(str, &res, 0);
  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(smartCalc_test_6) {
  double res = 0.0;
  char *str = "10.0+2^(2^(3))";
  int error = 0;
  error = from_answer(str, &res, 0);

  ck_assert_double_eq(res, 10 + pow(2, pow(2, 3)));
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_7) {
  double res = 0.0;
  char *str = "cos(99.0)/2^(sin(0.5))*10";
  int error = 0;
  error = from_answer(str, &res, 0);

  ck_assert_double_eq(res, cos(99.0) / pow(2, sin(0.5)) * 10);
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_8) {
  double res = 0.0;
  char *str = "7.2^(sin(55.0)-9^(cos(3.6))/7)";
  int error = 0;
  error = from_answer(str, &res, 0);

  ck_assert_double_eq(res, pow(7.2, (sin(55.) - pow(9, cos(3.6)) / 7)));
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_9) {
  double res = 0.0;
  char *str = "tan(2)-cos(45)+2^(sin(52))*5";
  int error = 0;
  error = from_answer(str, &res, 0);

  ck_assert_double_eq(res, tan(2) - cos(45) + pow(2, sin(52)) * 5);
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_10) {
  double res = 0.0;
  char *str = "ln(140)*log(49)";
  int error = 0;
  error = from_answer(str, &res, 0);

  ck_assert_double_eq(res, log(140) * log10(49));
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_11) {
  double res = 0.0;
  char *str = "sin(0.25)-cos(22.5)+tan(0.5)";
  int error = 0;
  error = from_answer(str, &res, 0);
  ck_assert_double_eq_tol(res, sin(0.25) - cos(22.5) + tan(0.5), 1e-7);
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_12) {
  double res = 0.0;
  char *str = "-1*2.5/sin(360)";
  int error = 0;
  error = from_answer(str, &res, 0);

  ck_assert_double_eq(res, -1 * 2.5 / sin(360));
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_13) {
  double res = 0.0;
  char *str = "-tan(45)*cos(45)/2^(sin(33))*(-5)";
  int error = 0;
  error = from_answer(str, &res, 0);

  ck_assert_double_eq(res, -tan(45) * cos(45) / pow(2, (sin(33))) * -5);
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_14) {
  double res = 0.0;
  char *str = "0.5/0";
  int error = 0;
  error = from_answer(str, &res, 0);
  ck_assert_int_eq(error, INF_RES);
}
END_TEST

START_TEST(smartCalc_test_15) {
  char *str = "(5)+()+(^)";
  int error = 0;
  double res = 0;
  error = from_answer(str, &res, 0);
  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(smartCalc_test_16) {
  double res = 0.0;
  char *str = "-99mod8-58mod23/88^(32mod5)";
  int error = 0;
  error = from_answer(str, &res, 0);
  ck_assert_double_eq(res, -99 % 8 - 58 % 23 / pow(88, (32 % 5)));
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_17) {
  double res = 0.0;
  char *str = "-81/(-9)-(-23)-(-25/0.5)*(-123-112)";
  int error = 0;
  error = from_answer(str, &res, 0);
  ck_assert_int_eq(res, -11718);
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_18) {
  double res = 0.0;
  char *str = "sqrt(25)-log(5)*100+ln(5)";
  int error = 0;
  error = from_answer(str, &res, 0);
  ck_assert_int_eq(res, -63.2875625);
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_19) {
  double res = 0.0;
  char *str = "acos(10mod3)-asin(1)+atan(1)";
  int error = 0;
  error = from_answer(str, &res, 0);
  ck_assert_int_eq(res, -0.7853981);
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_20) {
  double res = 0.0;
  char *str = "-10mod3";
  int error = 0;
  error = from_answer(str, &res, 0);
  ck_assert_int_eq(res, -1);
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_21) {
  double res = 0.0;
  char *str =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  int error = 0;
  error = from_answer(str, &res, 0);
  ck_assert_int_eq(res, -30.0721649485);
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_22) {
  double res = 0.0;
  char *str = "2^-2";
  int error = 0;
  error = from_answer(str, &res, 0);

  ck_assert_double_eq(res, 0);
  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(smartCalc_test_23) {
  double res = 0.0;
  char *str = "-ln(140)*log(49)";
  int error = 0;
  error = from_answer(str, &res, 0);

  ck_assert_double_eq(res, -log(140) * log10(49));
  ck_assert_int_eq(error, OK);
}
END_TEST

START_TEST(smartCalc_test_24) {
  double res = 0.0;
  char *str = "2x+1";
  int error = 0;
  error = from_answer(str, &res, 0);

  ck_assert_double_eq(res, 0);
  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(smartCalc_test_25) {
  double res = 0.0;
  char *str = "1+(1+2)x";
  int error = 0;
  error = from_answer(str, &res, 0);

  ck_assert_double_eq(res, 0);
  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(smartCalc_test_26) {
  double res = 0.0;
  char *str = "xx+2+1";
  int error = 0;
  error = from_answer(str, &res, 0);

  ck_assert_double_eq(res, 0);
  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(smartCalc_test_27) {
  double res = 0.0;
  char *str = "";
  int error = 0;
  error = from_answer(str, &res, 0);

  ck_assert_double_eq(res, 0);
  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(smartCalc_test_28) {
  double res = 0.0;
  char *str = ")2+1(";
  int error = 0;
  error = from_answer(str, &res, 0);

  ck_assert_double_eq(res, 0);
  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(smartCalc_test_29) {
  double res = 0.0;
  char *str = "1.1.1+2";
  int error = 0;
  error = from_answer(str, &res, 0);

  ck_assert_double_eq(res, 0);
  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(smartCalc_test_30) {
  double res = 0.0;
  char *str = "1+2+ln(2";
  int error = 0;
  error = from_answer(str, &res, 0);

  ck_assert_double_eq(res, 0);
  ck_assert_int_eq(error, INCORRECT_INPUT);
}
END_TEST

START_TEST(smartCalc_test_31) {
  char *str = "modx";
  double res = 0.0;
  int check = OK;
  check = from_answer(str, &res, 0);
  ck_assert_double_eq(res, 0);
  ck_assert_int_eq(check, INCORRECT_INPUT);
}
END_TEST

START_TEST(smartCalc_test_32) {
  char *str = "3/+6";
  double res = 0.0;
  int check = OK;
  check = from_answer(str, &res, 0);
  ck_assert_double_eq(res, 0);
  ck_assert_int_eq(check, INCORRECT_INPUT);
}
END_TEST

START_TEST(smartCalc_test_33) {
  char *str = "1.+.1";
  double res = 0;
  int check = OK;
  check = from_answer(str, &res, 0);
  ck_assert_int_eq(check, INCORRECT_INPUT);
}
END_TEST

START_TEST(polish_calc_1) {
  char input[255] = "2+2*2";
  double result = 0;
  double x_value = 0;
  int error = 0;
  // from_answer(input,1, x_value, &error);
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(2 + 2 * 2, result, 1e-7);
}
END_TEST

START_TEST(polish_calc_2) {
  char input[255] = "cos(30)";
  double result = 0;
  double x_value = 0;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(cos(30), result, 1e-7);
}
END_TEST

START_TEST(polish_calc_3) {
  char input[255] = "sin(30)";
  double result = 0;
  double x_value = 0;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(sin(30), result, 1e-7);
}
END_TEST

START_TEST(polish_calc_4) {
  char input[255] = "tan(30";
  double result = 0, x_value = 0.0;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(3, error);
}
END_TEST

START_TEST(polish_calc_5) {
  char input[255] = "acos(0.5)";
  double result = 0;
  double x_value = 0;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(acos(0.5), result, 1e-7);
}
END_TEST

START_TEST(polish_calc_6) {
  char input[255] = "asin(0.3)";
  double result = 0;
  double x_value = 0;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(asin(0.3), result, 1e-7);
}
END_TEST

START_TEST(polish_calc_7) {
  char input[255] = "atan(-0.3)";
  double result = 0;
  double x_value = 0;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(atan(-0.3), result, 1e-7);
}
END_TEST

START_TEST(polish_calc_8) {
  char input[255] = "sqrt(0.7)";
  double result = 0;
  double x_value = 0;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(sqrt(0.7), result, 1e-7);
}
END_TEST

START_TEST(polish_calc_9) {
  char input[255] = "ln(30)";
  double result = 0;
  double x_value = 0;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(log(30), result, 1e-7);
}
END_TEST

START_TEST(polish_calc_10) {
  char input[255] = "log(30)";
  double result = 0;
  double x_value = 0;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(log10(30), result, 1e-7);
}
END_TEST

START_TEST(polish_calc_11) {
  char input[255] = "2+7";
  double result = 0;
  double x_value = 0;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(2 + 7, result, 1e-7);
}
END_TEST

START_TEST(polish_calc_12) {
  char input[255] = "9146-5752";
  double result = 0;
  double x_value = 0;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(9146 - 5752, result, 1e-7);
}
END_TEST

START_TEST(polish_calc_13) {
  char input[255] = "3*(5*x+5)+1";
  double result = 0;
  double x_value = 4;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(3 * (5 * 4 + 5) + 1, result, 1e-7);
}
END_TEST

START_TEST(polish_calc_14) {
  char input[255] = "4*(2*x+2)+5*(3*x-5)";
  double result = 0;
  double x_value = 3;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(4 * (2 * 3 + 2) + 5 * (3 * 3 - 5), result, 1e-7);
}
END_TEST

START_TEST(polish_calc_15) {
  char input[255] = "5^(ln(3))";
  double result = 0;
  double x_value = 0;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(pow(5, log(3)), result, 1e-7);
}
END_TEST

START_TEST(polish_calc_16) {
  char input[255] = "sin(5)*12";
  double result = 0;
  double x_value = 0;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(sin(5) * 12, result, 1e-7);
}
END_TEST

START_TEST(polish_calc_17) {
  char input[255] = "cos(x)^2+sin(x)^2";
  double result = 0;
  double x_value = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(pow(cos(7), 2) + pow(sin(7), 2), result, 1e-7);
}
END_TEST

START_TEST(credit_ann) {
  double percents, month, sum, percents_result, result, monthly_pay = 0;
  percents = 40;
  month = 400;
  sum = 400;
  credit_evualete_ann(percents, month, sum, &percents_result, &result,
                      &monthly_pay);
  ck_assert_double_lt(427.9240000, result);
  ck_assert_double_lt(10.6981, monthly_pay);
  ck_assert_double_lt(27.9244, percents_result);
}
END_TEST

START_TEST(credit_dif) {
  double percents = 40, month = 12, sum = 400, percents_result = 0, result = 0;
  double monthly_pay[1024] = {0};
  credit_evualete_diff(percents, month, sum, &percents_result, &result,
                       monthly_pay);
  ck_assert_double_lt(408.6720000, result);
  ck_assert_double_lt(34.6484, monthly_pay[0]);
  ck_assert_double_lt(33.4466, monthly_pay[11]);
  ck_assert_double_lt(8.67215, percents_result);
}
END_TEST

START_TEST(polish_calc_18) {
  char input[255] = "sqrt(-1)";
  double x_value = 7, result = 0;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(polish_calc_19) {
  char input[255] = "4/0";
  double x_value = 0, result = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(INF_RES, error);
}
END_TEST

START_TEST(polish_calc_50) {
  char input[255] = "4/2+";
  double x_value = 0, result = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(polish_calc_55) {
  char input[255] = "2m";
  double x_value = 0, result = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(polish_calc_54) {
  char input[255] = "2+3cos";
  double x_value = 0, result = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(polish_calc_51) {
  char input[255] = "2+3acos";
  double x_value = 0, result = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(polish_calc_52) {
  char input[255] = "2+3ln";
  double x_value = 0, result = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(polish_calc_60) {
  char input[255] = "2+3sqrt";
  double x_value = 0, result = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(polish_calc_56) {
  char input[255] = "2+3log";
  double x_value = 0, result = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(polish_calc_57) {
  char input[255] = "x4";
  double x_value = 0, result = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(polish_calc_58) {
  char input[255] = ")2+3sqrt";
  double x_value = 0, result = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(polish_calc_59) {
  char input[255] = ")(2+3sqrt";
  double x_value = 0, result = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(polish_calc_20) {
  char input[255] = "log(-1)";
  double x_value = 0, result = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(NAN_RES, error);
}
END_TEST

START_TEST(polish_calc_21) {
  char input[255] = "ln(-1)";
  double x_value = 0, result = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(NAN_RES, error);
}
END_TEST

START_TEST(polish_calc_22) {
  char input[255] = "asin(2)";
  double x_value = 0, result = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(NAN_RES, error);
}
END_TEST

START_TEST(polish_calc_23) {
  char input[255] = "acos(3)";
  double x_value = 0, result = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(NAN_RES, error);
}
END_TEST

START_TEST(polish_calc_24) {
  char input[255] = "asin(1)";
  double result = 0;
  double x_value = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(asin(1), result, 1e-7);
}
END_TEST

START_TEST(polish_calc_25) {
  char input[255] = "acos(1)";
  double result = 0;
  double x_value = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(acos(1), result, 1e-7);
}
END_TEST

START_TEST(polish_calc_26) {
  char input[255] = "-48*12";
  double result = 0;
  double x_value = 7;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(-576, result, 1e-7);
}
END_TEST

START_TEST(polish_calc_27) {
  char input[255] = "5-(-5)";
  double result = 0;
  double x_value = 56;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(10, result, 1e-7);
}
END_TEST

START_TEST(polish_calc_28) {
  char input[255] = "10-23*(-27+1)";
  double result = 0;
  double x_value = 2;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(608, result, 1e-7);
}
END_TEST

START_TEST(polish_calc_29) {
  char input[255] = "5mod4";
  double result = 0;
  int error = 0;
  error = from_answer(input, &result, 0);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(1, result, 1e-7);
}
END_TEST

START_TEST(polish_calc_30) {
  char input[255] = "(-2.2)-2.2";
  double result = 0;
  double x_value = 2;
  int error = 0;
  error = from_answer(input, &result, x_value);
  ck_assert_int_eq(0, error);
  ck_assert_double_eq_tol(-4.4L, result, 1e-7);
}
END_TEST

Suite *s21_SmartCalc_suite() {
  Suite *s;

  s = suite_create("s21_SmartCalc");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, smartCalc_test_1);
  tcase_add_test(tc, smartCalc_test_2);
  tcase_add_test(tc, smartCalc_test_3);
  tcase_add_test(tc, smartCalc_test_4);
  tcase_add_test(tc, smartCalc_test_5);
  tcase_add_test(tc, smartCalc_test_6);
  tcase_add_test(tc, smartCalc_test_7);
  tcase_add_test(tc, smartCalc_test_8);
  tcase_add_test(tc, smartCalc_test_9);
  tcase_add_test(tc, smartCalc_test_10);
  tcase_add_test(tc, smartCalc_test_11);
  tcase_add_test(tc, smartCalc_test_12);
  tcase_add_test(tc, smartCalc_test_13);
  tcase_add_test(tc, smartCalc_test_14);
  tcase_add_test(tc, smartCalc_test_15);
  tcase_add_test(tc, smartCalc_test_16);
  tcase_add_test(tc, smartCalc_test_17);
  tcase_add_test(tc, smartCalc_test_18);
  tcase_add_test(tc, smartCalc_test_19);
  tcase_add_test(tc, smartCalc_test_20);
  tcase_add_test(tc, smartCalc_test_21);
  tcase_add_test(tc, smartCalc_test_22);
  tcase_add_test(tc, smartCalc_test_23);
  tcase_add_test(tc, smartCalc_test_24);
  tcase_add_test(tc, smartCalc_test_25);
  tcase_add_test(tc, smartCalc_test_26);
  tcase_add_test(tc, smartCalc_test_27);
  tcase_add_test(tc, smartCalc_test_28);
  tcase_add_test(tc, smartCalc_test_29);
  tcase_add_test(tc, smartCalc_test_30);
  tcase_add_test(tc, smartCalc_test_31);
  tcase_add_test(tc, smartCalc_test_32);
  tcase_add_test(tc, smartCalc_test_33);
  tcase_add_test(tc, polish_calc_1);
  tcase_add_test(tc, polish_calc_2);
  tcase_add_test(tc, polish_calc_3);
  tcase_add_test(tc, polish_calc_4);
  tcase_add_test(tc, polish_calc_5);
  tcase_add_test(tc, polish_calc_6);
  tcase_add_test(tc, polish_calc_7);
  tcase_add_test(tc, polish_calc_8);
  tcase_add_test(tc, polish_calc_9);
  tcase_add_test(tc, polish_calc_10);
  tcase_add_test(tc, polish_calc_11);
  tcase_add_test(tc, polish_calc_12);
  tcase_add_test(tc, polish_calc_13);
  tcase_add_test(tc, polish_calc_14);
  tcase_add_test(tc, polish_calc_15);
  tcase_add_test(tc, polish_calc_16);
  tcase_add_test(tc, polish_calc_17);
  tcase_add_test(tc, credit_ann);
  tcase_add_test(tc, credit_dif);
  tcase_add_test(tc, polish_calc_18);
  tcase_add_test(tc, polish_calc_19);
  tcase_add_test(tc, polish_calc_20);
  tcase_add_test(tc, polish_calc_21);
  tcase_add_test(tc, polish_calc_22);
  tcase_add_test(tc, polish_calc_23);
  tcase_add_test(tc, polish_calc_50);
  tcase_add_test(tc, polish_calc_51);
  tcase_add_test(tc, polish_calc_52);
  tcase_add_test(tc, polish_calc_54);
  tcase_add_test(tc, polish_calc_55);
  tcase_add_test(tc, polish_calc_56);
  tcase_add_test(tc, polish_calc_57);
  tcase_add_test(tc, polish_calc_58);
  tcase_add_test(tc, polish_calc_59);
  tcase_add_test(tc, polish_calc_60);
  tcase_add_test(tc, polish_calc_24);
  tcase_add_test(tc, polish_calc_25);
  tcase_add_test(tc, polish_calc_26);
  tcase_add_test(tc, polish_calc_27);
  tcase_add_test(tc, polish_calc_28);
  tcase_add_test(tc, polish_calc_29);
  tcase_add_test(tc, polish_calc_30);

  suite_add_tcase(s, tc);

  return s;
}

int main() {
  int failed = 0;
  Suite *suite = s21_SmartCalc_suite();
  SRunner *suite_runner = srunner_create(suite);

  srunner_set_fork_status(suite_runner, CK_NOFORK);
  srunner_run_all(suite_runner, CK_VERBOSE);

  failed = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}