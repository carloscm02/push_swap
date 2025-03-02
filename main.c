#include "push_swap.h"

int initialize_stack(t_stack *stack, int malloc_size)
{
    int i;
    stack->size = 0;
    stack->data = malloc(sizeof(int) * malloc_size);
    if (!stack->data)
        return 0;
    i = 0;
    while (i < malloc_size)
        stack->data[i++] = 0;
    return 1;
}

void load_stack(t_stack *stack, int argc, char *argv[])
{
    int i = 1;
    stack->size = argc - 1;
    while (i < argc) {
        stack->data[i - 1] = atoi(argv[i]);
        i++;
    }
}

void print_stack(t_stack *stack)
{
    for (int i = 0; i < stack->size; i++) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

int is_correct(t_stack *stackA){
    int i = 0;
    while(i + 1 < stackA->size){
        if (stackA->data[i] > stackA->data[i + 1])
            return 0;
        i++;
    }
    return 1;
}

void reset_operations(int *operation, int i) {
    int functions = 8;
    int j;
    j = i;
    while (j > 0 && operation[j] == functions) {
        j--;
    }

    if(j == 0 && operation[j] == functions) {
        while (operation[j]) {
            operation[j] = 1;
            j++;
        }
        operation[j] = 1;
    }else if (j == 0) {
        operation[j] += 1;
        while (operation[++j]) {
            operation[j] = 1;
        }
    }else{
        operation[j] += 1;
        while (operation[++j]) {
            operation[j] = 1;
        }
    }
}


void next_operation(int *operation){
// sa ra rra pb pa sb rb rrb ss rr  rrr
// 1  2  3   4  5  6  7  8   9  10  11
    int i = 0;
    int functions = 8;

    while (operation[i])
        i++;
    if (i > 0)
        i--;

    if (operation[i] == 0)
        operation[i] = 1;
    else if (operation[i] == functions)
        reset_operations(operation, i);
    else
        operation[i] += 1;
    // funcion para optimizar operaciones
}

void calculate_operations(t_stack *stackA, t_stack *stackB, int *operations){
// sa ra rra pb pa sb rb rrb ss rr  rrr
// 1  2  3   4  5  6  7  8   9  10  11
    int i = 0;

    while (operations[i]){
        if (operations[i] == 1)
            swap(stackA);
        else if (operations[i] == 2)
            rotate(stackA);
        else if (operations[i] == 3)
            reverse_rotate(stackA);
        else if (operations[i] == 4)
            push(stackB, stackA);
        else if (operations[i] == 5)
            push(stackA, stackB);
        else if (operations[i] == 6)
            swap(stackB);
        else if (operations[i] == 7)
            rotate(stackB);
        else if (operations[i] == 8)
            reverse_rotate(stackB);
        i++;
    }
}

void print_operations(int *operations)// poner la estructura como en el ejemplo
{
    int i = 0;

    while (operations[i]){
        if (operations[i] == 1)
            printf("sa ");
        else if (operations[i] == 2)
            printf("ra ");
        else if (operations[i] == 3)
            printf("rra ");
        else if (operations[i] == 4)
            printf("pb ");
        else if (operations[i] == 5)
            printf("pa ");
        else if (operations[i] == 6)
            printf("sb ");
        else if (operations[i] == 7)
            printf("rb ");
        else if (operations[i] == 8)
            printf("rrb ");
        i++;
    }
    printf("\n");
}

void brute_force(t_stack *stackA, t_stack *stackB, int argc, char *argv[]){
    int i;
    int *operations;
    int finish;

    operations = malloc(sizeof(int) * 100);
    if (!operations)
        return;
    i = 0;
    while (i < 10)
        operations[i++] = 0;
    finish = is_correct(stackA);
    while (!finish)
    {
        next_operation(operations);
        calculate_operations(stackA, stackB, operations);
        print_operations(operations); // Debug
        print_stack(stackA); // Debug
        print_stack(stackB); // Debug
        printf("\n"); // Debug
        finish = (stackA->size == argc - 1) && is_correct(stackA);
        if (!finish){
            free(stackA->data);
            free(stackB->data);
            initialize_stack(stackA, argc - 1);
            initialize_stack(stackB, 0);
            load_stack(stackA, argc, argv);
        }
    }
    print_operations(operations);
    free(operations);
}

int main(int argc, char *argv[]) {
    t_stack stackA;
    t_stack stackB;
    
    if (argc < 2)
        return (1);
    if (!are_numeric(argc, argv))
        return (printf("Error\n"), 1);
    if (!initialize_stack(&stackA, argc - 1))
        return (printf("Error al guardar memoria del Stack A\n"), 1);
    if (!initialize_stack(&stackB, argc - 1))
        return (printf("Error al guardar memoria del Stack B\n"), free(stackA.data), 1);
    load_stack(&stackA, argc, argv);
    if (has_duplicates(&stackA))
        return (free(stackA.data), free(stackB.data), printf("Error\n"), 1);

    printf("Stack A cargado exitosamente.\n");
    print_stack(&stackA);

    brute_force(&stackA, &stackB, argc, argv);

    printf("Stack A ordenado exitosamente.\n");
    print_stack(&stackA);

    return (free(stackA.data), free(stackB.data), 0);
}



