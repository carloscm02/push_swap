#include "push_swap.h"

void print_operations(int *operations)// poner la estructura como en el ejemplo
{
    int i = 0;

    while (operations[i]){
        if (operations[i] == 1)
            printf("1 ");
        else if (operations[i] == 2)
            printf("2 ");
        else if (operations[i] == 3)
            printf("3 ");
        else if (operations[i] == 4)
            printf("4 ");
        else if (operations[i] == 5)
            printf("5 ");
        else if (operations[i] == 6)
            printf("6 ");
        else if (operations[i] == 7)
            printf("7 ");
        else if (operations[i] == 8)
            printf("8 ");
        else if (operations[i] == 9)
            printf("9 ");
        else if (operations[i] == 10)
            printf("10 ");
        else if (operations[i] == 11)
            printf("11 ");
        i++;
    }
    printf("\n");
}

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

void reset_and_ad_one_more(int *operation){
    int i = 0;
    while (operation[i]) {
        operation[i] = 1;
        i++;
    }
    operation[i] = 1;
}

void reset_operations(int *operation, int i) {
    int functions = 11;
    int j;
    j = i;
    while (j > 0 && operation[j] == functions) {
        j--;
    }

    if(j == 0 && operation[j] == functions) {
        reset_and_ad_one_more(operation);
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


void next_operation(int *operation, int stack_initial_size){
// sa ra rra pb pa sb rb rrb ss rr  rrr
// 1  2  3   4  5  6  7  8   9  10  11
    print_operations(operation);

    int i = 0;
    int functions = 11;

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


    stack_initial_size += 0;

    optimice(operation, stack_initial_size);
}

void calculate_operations(t_stack *stackA, t_stack *stackB, int *operations){
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
        else if (operations[i] == 9){
            swap(stackA);
            swap(stackB);
        }
        else if (operations[i] == 10){
            rotate(stackA);
            rotate(stackB);
        }
        else if (operations[i] == 11){
            reverse_rotate(stackA);
            reverse_rotate(stackB);
        }
        i++;
    }
}

void brute_force(t_stack *stackA, t_stack *stackB, int argc, char *argv[]){
    int operaciones_totales = 0; // Debug
    int i;
    int *operations;
    int finish;

    operations = malloc(sizeof(int) * 100);
    if (!operations)
        return;
    i = 0;
    while (i < 100)
        operations[i++] = 0;
    finish = is_correct(stackA);
    while (!finish)
    {
        next_operation(operations, stackA->size);
        calculate_operations(stackA, stackB, operations);
        // print_operations(operations); // Debug
        // operaciones_totales++; // Debug
        // print_stack(stackA); // Debug
        // print_stack(stackB); // Debug
        // printf("\n"); // Debug
        finish = (stackA->size == argc - 1) && is_correct(stackA);
        if (!finish){
            free(stackA->data);
            free(stackB->data);
            initialize_stack(stackA, argc - 1);
            initialize_stack(stackB, 0);
            load_stack(stackA, argc, argv);
        }
        // printf("Operaciones totales: %d\n", operaciones_totales); // Debug
    }
    print_operations(operations);
    free(operations);
    printf("Operaciones totales: %d\n", operaciones_totales); // Debug
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

    // printf("Stack A cargado exitosamente.\n");
    // print_stack(&stackA);

    brute_force(&stackA, &stackB, argc, argv);

    // printf("Stack A ordenado exitosamente.\n");
    // print_stack(&stackA);

    return (free(stackA.data), free(stackB.data), 0);
}



