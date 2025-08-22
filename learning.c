#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double EPSILON = 1e-6;

double get_and_check_num(char ch);
double linear_roots(double b, double c, double * x1);
int solve_square(double a, double b, double c, double * x1, double * x2);
int square_roots(double a, double b, double c, double * x1, double * x2);

int less(double value);
int more(double value);
int near_zero(double value);

int main(void)
{
    double x1 = 0, x2 = 0;

    printf("Стандартный вид квадратного уравнения: a*(x**2) + b*x + c = 0\n");
    printf("Введите коэффициeнты a, b и c.\n");

    double a = get_and_check_num('a');
    double b = get_and_check_num('b');
    double c = get_and_check_num('c');

    solve_square(a, b, c, &x1, &x2);
}

double get_and_check_num(char ch) 
{
    double value = 0;

    printf("Введите коэффициент %c: ", ch);
    while (scanf("%lf", &value) != 1)
    {
        printf("Необходимо ввести число. Попробуйте ещё раз.\n");

        printf("Введите коэффициент %c: ", ch);
        trash();
    }

    return value;
}

void trash()
{
    while (getchar() != '\n')
        continue;
}

double linear_roots(double b, double c, double * x1)
{
    if (near_zero(b)) {
        if (near_zero(c)) {
            return 8;
        }
        else return 0;
    }
    else return 1;
}

int solve_square(double a, double b, double c, double * x1, double * x2)
{
    int num_of_roots = 0;
    if (near_zero(a)) {
        int num_of_roots = linear_roots(b, c, &x1);
    }
    else {
        int num_of_roots = square_roots(a, b, c, &x1, &x2);
        switch (num_of_roots)
        {
            case 0: 
                printf("Уравнение не имеет действительных корней.");
                break;
            case 1:
                printf("Уравнение имеет один действительный корень: x = %f", x1);
                break;
            case 2:
                printf("Уравнение имеет два действительных корня: x1 = %f, x2 = %f", x1, x2);
                break;
            case 8:
                printf("Уравнение имеет бесконечное число корней.");
                break;
            default: printf("An error has occurred");
        }
    }
}

int square_roots(double a, double b, double c, double * x1, double * x2)
{
    double discr = b*b - 4*a*c;
    if (less(discr)) return 0;
    else if (near_zero(discr)) {
        *x1 = (-c) / b;
        return 1;
    }
    else {
        *x1 = (-b + sqrt(discr)) / (2*a);
        *x2 = (-b - sqrt(discr)) / (2*a);
        return 2;
    }
}

int less(double value) 
{
    return value < -EPSILON;
}
int more(double value)
{
    return value > EPSILON;
}
int near_zero(double value)
{
    return value <= EPSILON && value >= -EPSILON;
}