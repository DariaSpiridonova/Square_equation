#include "io.h"

#include <string.h>

FILE *input_from_a_file(void)
{
    char name_of_file[21] = {0};
    FILE *fp = stdin;

    if (fgets(name_of_file, 21, stdin))
    {
        char *space = strchr(name_of_file, '\n');
        *space = '\0';

        fp = fopen(name_of_file, "r");
        if (fp == NULL)
            fp = stdin;
    }

    return fp;
}

void trash(void)
{
    while (getchar() != '\n')
        continue;
}

double get_and_check_num(char ch, FILE *fp)
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
        printf("Уравнение не имеет действительных корней.\n");
        break;
    case NUM_ONE:
        printf("Уравнение имеет один действительный корень: x = %f\n", x1);
        break;
    case NUM_TWO:
        printf("Уравнение имеет два действительных корня: x1 = %f, x2 = %f\n", x1, x2);
        break;
    case NUM_INFINITY:
        printf("Уравнение имеет бесконечное число корней.\n");
        break;
    default:
        printf("An error has occurred\n");
        break;
    }
}
