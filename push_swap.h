#ifndef PUSHSWAP_H
# define PUSHSWAP_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct s_stack {
    int *data;
    int size;
} t_stack;

int 	are_numeric(int argc, char *argv[]);
int		has_duplicates(t_stack *stack);
void	swap(t_stack *stack);
void	push(t_stack *stack_dest, t_stack *stack_orig);
void	rotate(t_stack *stack);
void	reverse_rotate(t_stack *stack);

#endif
