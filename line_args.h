#ifndef LINE_ARGS_H
#define LINE_ARGS_H

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

bool is_flag(const char *flag, const char *const *const argv, int i);
void add_coef(int *correct_commands, struct command *ptr, double *coefficient, const int argc, const char *const *const argv, int i);
void add_condition(int *correct_commands, bool *flag);

#endif