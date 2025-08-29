#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#include "io.h"
#include "solve.h"
#include "unit_test.h"
#include "line_args.h"

/*
assert(0);
abort()

MY_ASSERT(a > 5, "A must be more than 5")
    vfprintf() надо будет использьоват!
*/

void help(void);
void standart_mode(void);
void fast_mode(struct command superstruct);

int main(int argc, const char *const *const argv)
{
    struct command superstruct = parse_args(argc, argv);

    if (superstruct.has_help)
    {
        help();
        return 0;
    }
    if (superstruct.has_test)
    {
        main_test_all_square();
    }
    if (superstruct.has_args)
    {
        fast_mode(superstruct);
    }
    if (superstruct.has_interactive)
    {
        standart_mode();
    }

    return 0;
}

void help(void)
{
    printf("Command line flags:\n");

    const char *coef[] = {"-a", "a", "-b", "b", "-c", "c"};

    for (size_t i = 0; i < sizeof(coef) / sizeof(coef[0]); i += 2)
        printf("   %-10s         assigning a value to the coefficient %s (the default value is 0)\n", coef[i], coef[i + 1]);

    printf("   %-10s         conducting a unittest\n", "--test");
    printf("   %-10s      the usual mode of use", "--interactive");
}

void standart_mode(void)
{
    double x1 = 0, x2 = 0;

    printf("Стандартный вид квадратного уравнения: a*(x**2) + b*x + c = 0\n");
    printf("Введите коэффициeнты a, b и c.\n");

    printf("Если вы хотите осуществлять ввод из файла, введите имя файла, иначе нажмите q: ");

    FILE *fp = input_from_a_file();

    double a = get_and_check_num('a', fp);
    double b = get_and_check_num('b', fp);
    double c = get_and_check_num('c', fp);

    num_roots num_of_roots = solve_square(a, b, c, &x1, &x2);
    print_solution(num_of_roots, x1, x2);

    if (fp != stdin)
        fclose(fp);
}

void fast_mode(struct command superstruct)
{
    double x1 = 0, x2 = 0;

    num_roots num_of_roots = solve_square(superstruct.a, superstruct.b, superstruct.c, &x1, &x2);
    print_solution(num_of_roots, x1, x2);
}