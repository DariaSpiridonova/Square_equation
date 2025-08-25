#include "solve.h"

#include <assert.h>
#include <math.h>

#include "compare.h"

num_roots linear_roots(double b, double c, double *x1)
{
    if (is_near_num(b, 0))
    {
        if (is_near_num(c, 0))
        {
            return NUM_INFINITY;
        }
        else
            return NUM_ZERO;
    }
    else
    {
        *x1 = (-c) / b;
        if (is_near_num(*x1, -0))
            *x1 = 0;
        return NUM_ONE;
    }
}

num_roots solve_square(double a, double b, double c, double *x1, double *x2)
{
    assert(x1 != x2);

    enum num_roots num_of_roots = NUM_ZERO;
    if (is_near_num(a, 0))
    {
        num_of_roots = linear_roots(b, c, x1);
    }
    else
    {
        num_of_roots = square_roots(a, b, c, x1, x2);
    }

    return num_of_roots;
}

num_roots square_roots(double a, double b, double c, double *x1, double *x2)
{
    assert(x1 != x2);

    double discr = b * b - 4 * a * c;
    if (is_less_than_num(discr, 0))
    {
        return NUM_ZERO;
    }
    else if (is_near_num(discr, 0))
    {
        *x1 = (-b) / (2 * a);
        return NUM_ONE;
    }
    else
    {
        double sqrt_discr = sqrt(discr);
        *x1 = (-b + sqrt_discr) / (2 * a);
        *x2 = (-b - sqrt_discr) / (2 * a);
        return NUM_TWO;
    }
}