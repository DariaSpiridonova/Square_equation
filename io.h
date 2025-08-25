#ifndef IO_H
#define IO_H
#include <stdio.h>

#include "solve.h"

double get_and_check_num(char ch, FILE *fp);
void print_solution(num_roots num_of_roots, double x1, double x2);
void trash(void);

#endif