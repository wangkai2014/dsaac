#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

#define MAX_DIGIT_NUM  10000

enum arithmetric_operation
{
    ADDITION        = 1,
    SUBTRACTION     = 2,
    MULTIPLICATION  = 3,
    DIVISION        = 4,
    EXPONENTIATION  = 5,

    MAX_OPERATION
};

int add(char *first_operand, char *second_operand, char *answer);
int subtract(char *first_operand, char *second_operand, char *answer);
int multiply(char *first_operand, char *second_operand, char *answer);
int divide(char *first_operand, char *second_operand, char *answer);
int exponent(char *base, char *power, char *answer);

#endif
