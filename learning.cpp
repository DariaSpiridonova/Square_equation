// SquareSolver
/** @brief Решает квадратные уравнения
 *
 * @details Эта программа решает квадратное уравнения с заданными
 * коэффициентами (a, b и c).
 *
 * @param [in] a Коэффициент при x**2
 * @param [in] b Коэффициент при x
 * @param [in] c Свободный член
 *
 * @return Возвращает корни квадратного уравнения
 */

// Doxygen к функциям

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define WHITE "\x1b[0m"

const double EPSILON = 1e-6;

// Большими буквами NUM_ZERO
enum num_roots {
    NUM_ZERO,
    NUM_ONE,
    NUM_TWO,
    NUM_INFINITY = 8,
};

double get_and_check_num(char ch, FILE *fp);
void trash(void);
num_roots linear_roots(double b, double c, double *x1);
num_roots solve_square(double a, double b, double c, double *x1, double *x2);
num_roots square_roots(double a, double b, double c, double *x1, double *x2);
void print_solution(num_roots num_of_roots, double x1, double x2);

void test_solver_square(struct test_parameters test_par);
void num_of_test(void);
void main_test_all_square(void);

bool is_less_than_num(double value, double num);
bool is_more_than_num(double value, double num);
bool is_near_num(double value, double num);

struct test_parameters 
{
    double a; 
    double b;
    double c;
    int n;
    double root1;
    double root2;
};

struct test_parameters tests[] =
{
    {0, 0, 0, NUM_INFINITY, 0, 0},
    {0, 0, 1, NUM_ZERO, 0, 0},
    {1, 2, 1, NUM_ONE, -1.00, 0},
    {1, -5, 6, NUM_TWO, 3, 2},
    {1, 2, 5, NUM_ZERO, 0, 0},
    {0, 1, 2, NUM_ONE, -2.0, 0},
};


#define TEST

/** @brief Главная функция в программе
 *
 * @details Предлагает осуществить ввод из стандартного входного потока или из файла. Выводит в консоль коэффициенты квадратного уравнения,
 * предоставляя пользователю проверить корректность введённых данных. В неё возвращается из других функций количество корней уравнения и
 * результат выполнения программы.
 * 
 * @param [in] a Коэффициент при x**2
 * @param [in] b Коэффициент при x
 * @param [in] c Свободный член
 *
 * @return Возвращает корни квадратного уравнения
 */

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
#endif
}

/** @brief Проверяет корректность введённых данных
 *
 * @details Функция считывает данные из стандартного потока ввода или из файла и проверяет их корректность. Если данные с клавиатуры введены 
 * некорректно, пользователю предоставляется возможность повторного ввода.
 *
 * @param [in] ch Коэффициент квадратного уравнения
 * @param [in] fp Указатель на файл
 *
 * @return Возвращает значение коэффициента квадратного уравнения
 */

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

/** @brief Отбрасывает лишние символы в строке
 */
void trash(void)
{
    while (getchar() != '\n')
        continue;
}

num_roots linear_roots(double b, double c, double *x1)
{
    if (is_near_num(b, 0))
    {
        if (is_near_num(c, 0))
        {
            return NUM_INFINITY;
        }
        else
            return NUM_ZERO;
    }
    else
    {
        *x1 = (-c) / b;
        if (is_near_num(*x1, -0))
            *x1 = 0;
        return NUM_ONE;
    }
}

num_roots solve_square(double a, double b, double c, double *x1, double *x2)
{
    assert(x1 != x2);

    enum num_roots num_of_roots = NUM_ZERO;
    if (is_near_num(a, 0))
    {
        num_of_roots = linear_roots(b, c, x1);
    }
    else
    {
        num_of_roots = square_roots(a, b, c, x1, x2);
    }

    return num_of_roots;
}

num_roots square_roots(double a, double b, double c, double *x1, double *x2)
{
    assert(x1 != x2);

    double discr = b * b - 4 * a * c;
    if (is_less_than_num(discr, 0))
    {
        return NUM_ZERO;
    }
    else if (is_near_num(discr, 0))
    {
        *x1 = (-b) / (2 * a);
        return NUM_ONE;
    }
    else
    {
        double sqrt_discr = sqrt(discr);
        *x1 = (-b + sqrt_discr) / (2 * a);
        *x2 = (-b - sqrt_discr) / (2 * a);
        return NUM_TWO;
    }
}

bool is_less_than_num(double value, double num)
{
    return value < (-EPSILON + num);
}
bool is_more_than_num(double value, double num)
{
    return value > (EPSILON + num);
}
bool is_near_num(double value, double num)
{
    return value <= (EPSILON + num) && value >= (-EPSILON + num);
}

void print_solution(num_roots num_of_roots, double x1, double x2)
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

void main_test_all_square(void)
{
    for (int i = 0; i < 6; i++)
    {
        printf("TEST №%d: ", i + 1);
        test_solver_square(tests[i]);
    }
}

void test_solver_square(struct test_parameters test_par)
{
    double x1 = 0, x2 = 0;

    int nRoots = solve_square(test_par.a, test_par.b, test_par.c, &x1, &x2);

    if (nRoots != test_par.n)
        printf(RED "FAILED: SolveSquare(%lf, %lf, %lf, &x1, &x2) -> %d" WHITE, test_par.a, test_par.b, test_par.c, nRoots);

    switch (nRoots)
    {
        case 0:
        case 8:
            printf(GREEN "Программа отработала без ошибок.\n" WHITE);
            break;
        case 1:
            if (!(nRoots == 1 && is_near_num(x1, test_par.root1)))
                printf(RED "FAILED: x1 = %lf, x2 = %lf (should be x1 = " "\x1b[0m\n)", x1, x2);
            else
                printf(GREEN "Программа отработала без ошибок.\n" WHITE);
            break;
        case 2:
            if (!(nRoots == 2 && is_near_num(x1, test_par.root1) && is_near_num(x2, test_par.root2)))
                printf(RED "FAILED: SolveSquare(0, 0, 0, &x1, &x2) -> NUM_INFINITY, x1 = %lf, x2 = %lf (should be an infinite number of roots\n" "\x1b[0m)", x1, x2);
            else
                printf(GREEN "Программа отработала без ошибок.\n" WHITE);
            break;
        default:
            printf(RED "AN ERROR HAS OCCURRED\n" WHITE);
    }
}

void num_of_test(void)
{
    static int i = 1;

    printf("TEST №%d: ", i++);
}