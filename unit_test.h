#ifndef UNITTEST_H
#define UNITTEST_H

#include <stdlib.h>

#include "solve.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define WHITE "\x1b[0m"

void test_solver_square(struct test_parameters test_par, int *failed);
void main_test_all_square(void);

struct test_parameters
{
    double a;
    double b;
    double c;
    int n;
    double root1;
    double root2;
};

const struct test_parameters tests[] =
{
    {0, 0, 0, NUM_INFINITY, 0, 0},
    {0, 0, 1, NUM_ZERO, 0, 0},
    {1, 2, 1, NUM_ONE, -1.00, 0},
    {1, -5, 6, NUM_TWO, 3, 2},
    {1, 2, 5, NUM_ZERO, 0, 0},
    {0, 1, 2, NUM_ONE, -2.0, 0},
};

const size_t quantity_test_elements = sizeof(tests) / sizeof(tests[1]);

#endif