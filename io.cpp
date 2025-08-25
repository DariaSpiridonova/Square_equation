#include "io.h"

void trash(void)
{
    while (getchar() != '\n')
        continue;
}

double get_and_check_num(char ch, FILE *fp) // input
{
    double value = 0;

    if (fp == stdin)
        printf("Введите коэффициент %c: ", ch);

    while (fscanf(fp, "%lf", &value) != 1)
    {
        printf("Необходимо ввести число. Попробуйте ещё раз.\n");

        printf("Введите коэффициент %c: ", ch);
        trash();
    }

    return value;
}

void print_solution(num_roots num_of_roots, double x1, double x2) // output
{
    switch (num_of_roots)
    {
    case NUM_ZERO:
        printf("Уравнение не имеет действительных корней.");
        break;
    case NUM_ONE:
        printf("Уравнение имеет один действительный корень: x = %f", x1);
        break;
    case NUM_TWO:
        printf("Уравнение имеет два действительных корня: x1 = %f, x2 = %f", x1, x2);
        break;
    case NUM_INFINITY:
        printf("Уравнение имеет бесконечное число корней.");
        break;
    default:
        printf("An error has occurred");
        break;
    }
}
