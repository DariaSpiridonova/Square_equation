#ifndef COMPARE_H
#define COMPARE_H
bool is_less_than_num(double value, double num);
bool is_more_than_num(double value, double num);
bool is_near_num(double value, double num);

const double EPSILON = 1e-6;

#endif