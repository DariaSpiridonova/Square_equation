#include "unit_test.h"

#include <stdio.h>
#include "compare.h"
#include "solve.h"

void main_test_all_square(void)
{
    int failed = 0;

    for (int i = 0; i < quantity_test_elements; i++)
    {
        printf("TEST №%d: ", i + 1);
        test_solver_square(tests[i], &failed);
    }

    printf("Количество проваленных тестов = %d", failed);
}

void test_solver_square(struct test_parameters test_par, int * failed)
{
    double x1 = 0, x2 = 0;

    int nRoots = solve_square(test_par.a, test_par.b, test_par.c, &x1, &x2);

    if (nRoots != test_par.n) {
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
            if (!(nRoots == 1 && is_near_num(x1, test_par.root1))) {
                printf(RED "FAILED: x1 = %lf, x2 = %lf (should be x1 = " "\x1b[0m\n)", x1, x2);
                *failed += 1;
            }
            else
                printf(GREEN "Программа отработала без ошибок.\n" WHITE);
            break;
        case 2:
            if (!(nRoots == 2 && is_near_num(x1, test_par.root1) && is_near_num(x2, test_par.root2))) {
                printf(RED "FAILED: SolveSquare(0, 0, 0, &x1, &x2) -> NUM_INFINITY, x1 = %lf, x2 = %lf (should be an infinite number of roots\n" "\x1b[0m)", x1, x2);
                *failed += 1; 
            }
                else
                printf(GREEN "Программа отработала без ошибок.\n" WHITE);
            break;
        default:
            printf(RED "AN ERROR HAS OCCURRED\n" WHITE);
    }
}