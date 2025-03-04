#include "push_swap.h"

void swap(t_stack *stack)
{
    int tmp;

    if (stack->size < 2)
        return;
    tmp = stack->data[0];
    stack->data[0] = stack->data[1];
    stack->data[1] = tmp;
}

void push(t_stack *stack_dest, t_stack *stack_orig)
{
    int i;
    if (stack_orig->size == 0)
        return;
    i = stack_dest->size;
    while (i > 0)
    {
        stack_dest->data[i] = stack_dest->data[i - 1];
        i--;
    }
    stack_dest->data[0] = stack_orig->data[0];
    stack_dest->size++;
    i = 0;
    while (i < stack_orig->size - 1)
    {
        stack_orig->data[i] = stack_orig->data[i + 1];
        i++;
    }
    stack_orig->size--;
}

void rotate(t_stack *stack)
{
    int tmp;
    int i;

    if (stack->size < 2)
        return;

    tmp = stack->data[0]; // Guardamos el primer elemento
    i = 0;
    while (i < stack->size - 1)
    {
        stack->data[i] = stack->data[i + 1]; // Desplazamos los elementos hacia la izquierda
        i++;
    }
    stack->data[stack->size - 1] = tmp; // Colocamos el primer elemento al final
}

void reverse_rotate(t_stack *stack)
{
    int tmp;
    int i;

    if (stack->size < 2)
        return;

    tmp = stack->data[stack->size - 1]; // Guardamos el último elemento
    i = stack->size - 1;
    while (i > 0)
    {
        stack->data[i] = stack->data[i - 1]; // Desplazamos los elementos hacia la derecha
        i--;
    }
    stack->data[0] = tmp; // Colocamos el último elemento al inicio
}
