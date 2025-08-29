#include "compare.h"
#include <math.h>

bool is_less_than_num(double value, double num)
{
    return value < (-EPSILON + num);
}
bool is_more_than_num(double value, double num)
{
    return value > (EPSILON + num);
}
bool is_near_num(double value, double num)
{
    return fabs(value - num) <= EPSILON;
}
