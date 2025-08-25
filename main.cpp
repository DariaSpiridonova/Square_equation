#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

#include "io.h"
#include "solve.h" 
#include "unit_test.h"

int main(void)
{
#ifdef TEST
    main_test_all_square();
#else
    double x1 = 0, x2 = 0;

    printf("Стандартный вид квадратного уравнения: a*(x**2) + b*x + c = 0\n");
    printf("Введите коэффициeнты a, b и c.\n");

    printf("Если вы хотите осуществлять ввод из файла, введите имя файла, иначе нажмите q: ");

    char name_of_file[21] = {0};
    FILE *fp = stdin;

    if (fgets(name_of_file, 21, stdin))
    {
        char * space = strchr(name_of_file, '\n');
        *space = '\0';
        if (!(fp = fopen(name_of_file, "r")))
            fp = stdin;
        printf("<%s>\n", name_of_file);
    }

    double a = get_and_check_num('a', fp);
    double b = get_and_check_num('b', fp);
    double c = get_and_check_num('c', fp);

    printf("%f %f %f\n", a, b, c);

    num_roots num_of_roots = solve_square(a, b, c, &x1, &x2);
    print_solution(num_of_roots, x1, x2);

    if (fp != stdin)
        fclose(fp);

    return 0;
#endif
}