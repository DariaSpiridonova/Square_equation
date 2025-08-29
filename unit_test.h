#ifndef UNITTEST_H
#define UNITTEST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "solve.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define WHITE "\x1b[0m"

#define TEST

struct test_parameters *tests_from_a_file(int *quantity_test_elements);
void test_solver_square(struct test_parameters test_par, int *failed);
void main_test_all_square(void);
bool write_to_array(char *buf, int num_of_spaces, struct test_parameters *tests);
int file_size(FILE *fp);
char * get_buffer_from_file(FILE * fp, int length);
int count_newlines(const char *buffer, int length);

struct test_parameters
{
    double a;
    double b;
    double c;
    int n;
    double root1;
    double root2;
};

#endif