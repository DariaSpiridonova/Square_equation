#include "line_args.h"

#include <string.h>
#include <stdlib.h>

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