#include "unit_test.h"

#include <stdio.h>
#include "compare.h"
#include "solve.h"
#include <string.h>

const char NAME_OF_FILE[] = "unittests.txt";

struct test_parameters *  tests_from_a_file(int * quantity_test_elements)
{
    FILE *fp = fopen(NAME_OF_FILE, "r");
    if (!fp)
    {
        printf("Ошибка");
        return NULL;
    }
    int length = file_size(fp);

    char *buffer = (char *)calloc(length + 1, sizeof(char));

    fread(buffer, sizeof(char), length, fp);
    fclose(fp);

    buffer[length] = '\0';

    *quantity_test_elements = count_newlines(buffer, length);

    struct test_parameters *tests = (struct test_parameters *)calloc(*quantity_test_elements, sizeof(struct test_parameters));
    char *buf = buffer;

    write_to_array(buf, *quantity_test_elements, tests);

    free(buffer);

    return tests;
}

int file_size(FILE *fp)
{
    fseek(fp, 0, SEEK_END);
    int length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    return length;
}

int count_newlines(const char *buffer, int length)
{
    int num_of_spaces = 0;

    for (int i = 0; i < length; i++)
    {
        if (buffer[i] == '\n')
            num_of_spaces++;
    }

    return num_of_spaces;
}

void write_to_array(char *buf, int num_of_spaces, struct test_parameters * tests)
{
    for (int i = 0; i < num_of_spaces; i++)
    {
        sscanf(buf, "%lf, %lf, %lf, %d, %lf, %lf",
               &tests[i].a,
               &tests[i].b,
               &tests[i].c,
               &tests[i].n,
               &tests[i].root1,
               &tests[i].root2);

        buf = strchr(buf, '\n') + 1;
    }
}

void main_test_all_square(void)
{
    int quantity_test_elements = 0;

    struct test_parameters * tests = tests_from_a_file(&quantity_test_elements);
    int failed = 0;

    for (int i = 0; i < quantity_test_elements; i++)
    {
        printf("TEST №%d: ", i + 1);
        test_solver_square(tests[i], &failed);
    }

    free(tests);

    printf("Количество проваленных тестов = %d", failed);
}

void test_solver_square(struct test_parameters test_par, int *failed)
{
    double x1 = 0, x2 = 0;

    int nRoots = solve_square(test_par.a, test_par.b, test_par.c, &x1, &x2);

    if (nRoots != test_par.n)
    {
        printf(RED "FAILED: SolveSquare(%lf, %lf, %lf, &x1, &x2) -> %d" WHITE, test_par.a, test_par.b, test_par.c, nRoots);
        *failed += 1;
    }

    switch (nRoots)
    {
        case 0:
        case 8:
            printf(GREEN "Программа отработала без ошибок.\n" WHITE);
            break;
        case 1:
            if (!(nRoots == 1 && is_near_num(x1, test_par.root1)))
            {
                printf(RED "FAILED: x1 = %lf, x2 = %lf (should be x1 = "
                        "\x1b[0m\n)",
                    x1, x2);
                *failed += 1;
            }
            else
                printf(GREEN "Программа отработала без ошибок.\n" WHITE);
            break;
        case 2:
            if (!(nRoots == 2 && is_near_num(x1, test_par.root1) && is_near_num(x2, test_par.root2)))
            {
                printf(RED "FAILED: SolveSquare(0, 0, 0, &x1, &x2) -> NUM_INFINITY, x1 = %lf, x2 = %lf (should be an infinite number of roots\n"
                        "\x1b[0m)",
                    x1, x2);
                *failed += 1;
            }
            else
                printf(GREEN "Программа отработала без ошибок.\n" WHITE);
            break;
        default:
            printf(RED "AN ERROR HAS OCCURRED\n" WHITE);
    }
}