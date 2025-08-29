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

FILE *input_from_a_file(void);

/*
assert(0);
abort()

MY_ASSERT(a > 5, "A must be more than %d, %s", 5, "Hello World!")
    vfprintf() надо будет использьоват!
*/

struct command
{
    bool has_args;
    double a;
    double b;
    double c;
    bool has_test;
    bool has_interactive;
    bool has_help;
};

struct command parse_args(int argc, const char *const *const argv);
void help(void);
void standart_mode(void);
void fast_mode(struct command superstruct);

bool is_flag(const char *flag, const char *const *const argv, int i);
void add_coef(int *correct_commands, struct command *ptr, double *coefficient, const int argc, const char *const *const argv, int i);
void add_condition(int *correct_commands, bool *flag);

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

struct command parse_args(int argc, const char *const *const argv)
{
    struct command superstruct = {};

    int correct_commands = 0;

    if (argc < 2)
    {
        superstruct.has_help = true;
        return superstruct;
    }

    for (int i = 1; i < argc; i++)
    {
        if      (is_flag("-a", argv, i)) add_coef(&correct_commands, &superstruct, &(superstruct.a), argc, argv, i);
        else if (is_flag("-b", argv, i)) add_coef(&correct_commands, &superstruct, &(superstruct.b), argc, argv, i);
        else if (is_flag("-c", argv, i)) add_coef(&correct_commands, &superstruct, &(superstruct.c), argc, argv, i);
        else if (is_flag("--test",        argv, i)) add_condition(&correct_commands, &(superstruct.has_test));
        else if (is_flag("--interactive", argv, i)) add_condition(&correct_commands, &(superstruct.has_interactive));
        else if (is_flag("--help",        argv, i)) add_condition(&correct_commands, &(superstruct.has_help));
    }

    if (argc != correct_commands + 1)
        superstruct.has_help = true;

    return superstruct;
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

bool is_flag(const char *flag, const char *const *const argv, int i)
{
    return !strcmp(argv[i], flag);
}

void add_coef(int *correct_commands, struct command *ptr, double *coefficient, const int argc, const char *const *const argv, int i)
{
    (*correct_commands)++;
    ptr->has_args = true;
    char *ptr_error;

    if (i < argc - 1)
    {
        double val = strtod(argv[i + 1], &ptr_error);
        if (*ptr_error == '\0')
        {
            (*correct_commands)++;
            *coefficient = val;
        }
    }
}

void add_condition(int *correct_commands, bool *flag)
{
    (*correct_commands)++;
    *flag = true;
}