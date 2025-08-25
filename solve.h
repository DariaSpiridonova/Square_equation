#ifndef SOLVE_H
#define SOLVE_H

enum num_roots {
    NUM_ZERO,
    NUM_ONE,
    NUM_TWO,
    NUM_INFINITY = 8,
};

num_roots linear_roots(double b, double c, double *x1);
num_roots solve_square(double a, double b, double c, double *x1, double *x2);
num_roots square_roots(double a, double b, double c, double *x1, double *x2);

#endif