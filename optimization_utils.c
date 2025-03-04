#include "push_swap.h"
//     int i = start;
//     while (operation[i]) {
//         operation[i] = operation[i + 1];
//         i++;
//     }
// }

int optimiced_sa(int *operation, int stackA_size){
    int changes = 0;
    int current_size = stackA_size;
    int i = 0;

    while (operation[i])
    {
        if (operation[i] == 4)
            current_size--;
        if (operation[i] == 5)
            current_size++;
        if (operation[i] == 1 && current_size < 2){// sa cuando stackA tiene menos de 2 elementos
            operation[i] = 2;
            changes = 1;
        }
        if (i > 0 && operation[i] == 1){ // si el anterior es un sa/sb/ss no hago otro sb
            if (operation[i - 1] == 1 ||
                operation[i - 1] == 6 ||
                operation[i - 1] == 9){
                operation[i] = 2;
                changes = 1;
            }
        }
        i++;
    }
    return changes;
}

int optimiced_ra(int *operation, int stackA_size){
    int changes = 0;
    int consecutive_ra = 0;
    int current_size = stackA_size;
    int i = 0;

    while(operation[i]){
        if (operation[i] == 4)
            current_size--;
        if (operation[i] == 5)
            current_size++;
        if (operation[i] == 2){
            consecutive_ra++;// si ra da la vuelta o mas / el estackA tiene menos de 2 elementos
            if (current_size <= consecutive_ra || current_size < 2){
                operation[i] = 3;
                changes = 1;
            }
        }
        else
            consecutive_ra = 0;
        i++;
    }
    return changes;
}

int optimiced_rra(int *operation, int stackA_size){
    int changes = 0;
    int consecutive_rra = 0;
    int current_size = stackA_size;
    int i = 0;

    while(operation[i]){
        if(operation[i] == 4) // mira a ver si esta dando una vuelta completa en el stackA
            current_size--;
        else if (operation[i] == 5)
            current_size++;
        else if(operation[i] == 3){
            consecutive_rra++;
            if (current_size <= consecutive_rra || current_size < 2){
                operation[i] = 4;
                changes = 1;
            }
        }else
            consecutive_rra = 0;
        if (i && operation[i - 1] == 2 && operation[i] == 3){ // si este es un rra y el anterior es un ra paso a pa siguiente
            operation[i] = 4;
            changes = 1;
        }
        i++;
    }
    return changes;
}


int optimiced_pb(int *operation, int stackA_size){
    int changes = 0;
    int stackB_current_size = 0;
    int i = 0;

    while (operation[i]){
        if (operation[i] == 4){
            if(stackA_size - stackB_current_size < 1){
                operation[i] = 5;
                changes = 1;
            }
            stackB_current_size++;
        }
        if (operation[i] == 5)
            stackB_current_size--;
        if (i > 0 && operation[i] == 4 && operation[i - 1] == 5){
            operation[i] = 5;
            changes = 1;
        }
        i++;
    }
    return changes;
}

int optimiced_pa(int *operation, int stackA_size){
    int changes = 0;
    int i = 0;

    while (operation[i]){
        if (operation[i] == 4){
            if(stackA_size < 1){
                operation[i] = 6;
                changes = 1;
            }
            stackA_size--;
        }
        if (operation[i] == 5)
            stackA_size++;
        if (i > 0 && operation[i] == 5 && operation[i - 1] == 4){
            operation[i] = 6;
            changes = 1;
        }
        i++;
    }
    return changes;
}

int optimiced_p(int *operation){
    int changes = 0;
    int amount_pb = 0;
    int amount_pa = 0;
    int i = 0;

    while (operation[i]){
        if (operation[i] == 4)// pb
            amount_pb++;
        if (operation[i] == 5){// pa
            if (++amount_pa > amount_pb){
                operation[i] = 6;
                changes = 1;
            }
        }
        i++;
    }
    return changes;
    // if (amount_pb != amount_pa) // si al finalinar no hay tantos pa como pb, pasamos a la siguinete
    //     next_operation(operation, stackA_size);
}

int optimiced_sb(int *operation){
    int changes = 0;
    int stackB_current_sice = 0;
    int i = 0;

    while (operation[i]){
        if(operation[i] == 4)
            stackB_current_sice++;
        else if (operation[i] == 5)
            stackB_current_sice--;
        if (operation[i] == 6){
            if(stackB_current_sice < 2){// si se intenta hacer un sb pero stackb esta vacio o tiene uno...
                operation[i] = 7;
                changes = 1;
            }
            if (i){ // si el anterior es un sa/sb/ss no hago otro sb
                if (operation[i - 1] == 1 ||
                    operation[i - 1] == 6 ||
                    operation[i - 1] == 9){
                    operation[i] = 7;
                    changes = 1;
                }
            }
        }
        i++;
    }
    return changes;
}





int optimiced_rb(int *operation){
    int changes = 0;
    int consecutive_rb = 0;
    int current_size = 0;
    int i = 0;

    while(operation[i]){
        if (i > 0 && ((operation[i - 1] == 8 && operation[i] == 7) ||// si este es un rb y el anterior es un rrb paso a pa siguiente
            (operation[i - 1] == 2 && operation[i] == 7))){// este es rb y el anterior es ra (rr)
            operation[i] = 8;
            changes = 1;
        }
        if(operation[i] == 4)// pb
            current_size++;
        else if (operation[i] == 5)// pa
            current_size--;
        if(operation[i] == 7){
            consecutive_rb++;
            if ((current_size <= consecutive_rb) || current_size < 2){
                operation[i] = 8;
                changes = 1;
            }
        }else
            consecutive_rb = 0;
        i++;
    }
    return changes;
}

void optimiced_rrb(int *operation, int stackA_size){
    int consecutive_rrb = 0;
    int current_size = 0;
    int i = 0;

    while(operation[i]){
        if (i && operation[i - 1] == 7 && operation[i] == 8){ // si este es un rra y el anterior es un ra paso a pa siguiente
            next_operation(operation, stackA_size);
            return;
        }
        if(operation[i] == 4) // mira a ver si esta dando una vuelta completa en el stackA
            current_size++;
        else if (operation[i] == 5)
            current_size--;
        if(operation[i] == 8){
            consecutive_rrb++;
            if (current_size == consecutive_rrb || current_size < 2){
                next_operation(operation, stackA_size);
                return;
            }
        }else
            consecutive_rrb = 0;
        i++;
    }
}

void optimiced_ss(int *operation, int stackA_size){
    int current_size_a = stackA_size;
    int i = 0;

    while (operation[i]){
        if(operation[i] == 4)
            current_size_a--;
        if(operation[i] == 5)
            current_size_a++;
        if(operation[i] == 9){
            if (current_size_a < 2 ||
                stackA_size - current_size_a < 2){
                next_operation(operation, stackA_size);
                return; 
                }
            if (!i)
            {
                next_operation(operation, stackA_size);
                return;  
            }else {
                if (operation[i - 1] == 1 ||
                    operation[i - 1] == 6 ||
                    operation[i - 1] == 9){
                    next_operation(operation, stackA_size);
                    return;
                }
            }
        }
        i++;
    }
}

void optimiced_rr(int *operation, int stackA_size){
    int size_stack_a = stackA_size;
    int consecutive_rr = 0;
    int i = 0;

    while (operation[i]){
        if(operation[i] == 4)
            size_stack_a--;
        if(operation[i] == 5)
            size_stack_a++;
        if(operation[i] == 10){
            consecutive_rr++;
            if (size_stack_a <= consecutive_rr ||
                stackA_size - size_stack_a <= consecutive_rr
            ){
                next_operation(operation, stackA_size);
                return;
            }
            if (!i)
            {
                next_operation(operation, stackA_size);
                return;  
            } else if (operation[i - 1] == 11){
                next_operation(operation, stackA_size);
                return;  
            }
        }else
            consecutive_rr = 0;
        i++;
    }
}

void optimiced_rrr(int *operation, int stackA_size){
    int size_stack_a = stackA_size;
    int consecutive_rrr = 0;
    int i = 0;

    while (operation[i]){
        if(operation[i] == 4)
            size_stack_a--;
        if(operation[i] == 5)
            size_stack_a++;
        if(operation[i] == 11){
            consecutive_rrr++;
            if (size_stack_a <= consecutive_rrr ||
                stackA_size - size_stack_a <= consecutive_rrr
            ){
                next_operation(operation, stackA_size);
                return;
            }
            if (!i)
            {
                next_operation(operation, stackA_size);
                return;  
            } else if (operation[i - 1] == 10){
                next_operation(operation, stackA_size);
                return;  
            }
        }else
            consecutive_rrr = 0;
        i++;
    }
}


void optimice(int *operation, int stackA_size){
    
    while (optimiced_sa(operation, stackA_size) ||
    optimiced_ra(operation, stackA_size) ||
    optimiced_rra(operation, stackA_size) ||
    optimiced_pb(operation, stackA_size) ||
    optimiced_pa(operation, stackA_size) ||
    optimiced_p(operation) ||
    optimiced_sb(operation) ||
    optimiced_rb(operation));

    // optimiced_p(operation, stackA_size);
    // optimiced_rb(operation);
    // optimiced_rrb(operation, stackA_size);
    // optimiced_ss(operation, stackA_size);
    // optimiced_rr(operation, stackA_size);
    // optimiced_rrr(operation, stackA_size);
}