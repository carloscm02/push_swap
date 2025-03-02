#include "push_swap.h"

int is_integer(char *str)
{
    int i = 0;
    long num = 0;
    int sign = 1;

    if (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] != '\0') {
        num = num * 10 + (str[i] - '0');
        num *= sign;
        sign = 1;
        if (num > 2147483647 || num < -2147483648)
            return 0;
        i++;
    }
    return 1;
}

int are_numeric(int argc, char *argv[])
{
    int i = 1;
    int j;

    while (i < argc) {
        j = 0;
        if (argv[i][j] == '-' || argv[i][j] == '+')
            j++;
        while (argv[i][j] != '\0') {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return 0;
            j++;
        }
        if (!is_integer(argv[i]))
            return 0;
        i++;
    }

    return 1;
}

int has_duplicates(t_stack *stack)
{
    for (int i = 0; i < stack->size; i++) {
        for (int j = i + 1; j < stack->size; j++) {
            if (stack->data[i] == stack->data[j]) {
                return 1;
            }
        }
    }
    return 0;
}