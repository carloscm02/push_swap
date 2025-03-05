#include "push_swap.h"


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
        if (operation[i] == 4){ // si se intenta pasar de 'a' a 'b' y a es 0
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
    int count_pa = 0;
    int count_pb = 0;
    int changes = 0;
    int i = 0;

    while (operation[i]){
        if (operation[i] == 5){// controla que no haya un 'pa' antes que un 'pb'
            count_pa++;
            if(count_pa > count_pb){
                operation[i] = 6;
                changes = 1;
                count_pa--;
            }
        }
        if (operation[i] == 4)
        count_pb++;
        if (operation[i] == 5){
            if (stackA_size - count_pb + count_pa < 0){
                operation[i] = 6;
                changes = 1;
            }
            if (i > 0 && operation[i - 1] == 4){
                operation[i] = 6;
                changes = 1;
                count_pa--;
            }
        }
        i++;
    }
    return changes;
}

int optimiced_p(int *operation){
    int changes = 0;
    int impar = 0;
    int amount_pb = 0;
    int amount_pa = 0;
    int i = 0;

    while (operation[i]){
        if (operation[i] == 4)// pb
            amount_pb++;
        if (operation[i] == 5){// pa
            amount_pa++;
        }
        i++;
    }
    i--;
    if ((amount_pa + amount_pb) > 0 && (amount_pa + amount_pb) % 2 == 1){
        impar = 1;
    }
    while (amount_pb - amount_pa != 0){
        if (operation[i] == 4){
            if (impar){
                operation[i] = 6;
                amount_pb--;
            }
            else if (amount_pb > amount_pa) {
                operation[i] = 5;
                amount_pa++;
                amount_pb--;
            }
        }
        if (operation[i] == 5){
            if (impar){
                operation[i] = 6;
                amount_pa--;
            }
            else if (amount_pa > amount_pb){
                operation[i] = 6;
                amount_pa--;
            }
        }
        i--;
        changes = 1;
    }
    
    return changes;
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

int optimiced_rrb(int *operation){
    int changes = 0;
    int consecutive_rrb = 0;
    int current_size = 0;
    int i = 0;

    while(operation[i]){
        if (i && ((operation[i - 1] == 7 && operation[i] == 8) || // si el anterior es un ra paso a pa siguiente
        (operation[i - 1] == 7 && operation[i] == 8))){// si el anterior es un rr paso a pa siguiente
            changes = 1;
            operation[i] = 9;
        }
        if(operation[i] == 4) // mira a ver si esta dando una vuelta completa en el stackA
            current_size++;
        else if (operation[i] == 5)
            current_size--;
        if(operation[i] == 8){
            consecutive_rrb++;
            if (current_size <= consecutive_rrb || current_size < 2){
                changes = 1;
                operation[i] = 9;
            }
        }else
            consecutive_rrb = 0;
        i++;
    }
    return changes;
}

int optimiced_ss(int *operation, int stackA_size){ //sa y sb
    int changes = 0;
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
                changes = 1;
                operation[i] = 10;
                }
            if (i == 0)
            {
                changes = 1;
                operation[i] = 10;
            }else {
                if (operation[i - 1] == 1 ||
                    operation[i - 1] == 6 ||
                    operation[i - 1] == 9){
                        changes = 1;
                        operation[i] = 10;
                }
            }
        }
        i++;
    }
    return changes;
}

int optimiced_rr(int *operation, int stackA_size){ // ra y rb (10)
    int changes = 0;
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
                changes = 1;
                operation[i] = 11;
            }
            if (i == 0)
            {
                changes = 1;
                operation[i] = 11;
            } else if (operation[i - 1] == 11){
                changes = 1;
                operation[i] = 11;
            }
        }else
            consecutive_rr = 0;
        i++;
    }
    return changes;
}



void optimiced_rrr(int *operation, int stackA_size){ // rra y rrb (11)
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
            if (i == 0)
            {
                reset_and_ad_one_more(operation); // esta funcion me imprime una linea de más que es incorrecta(1 1 1 1 1 1)
                return;
            }
            else{
                if (operation[i - 1] == 10){
                    operation[i - 1] = 11;
                    operation[i] = 1;
                    return;
                }
                if (operation[i - 1] != 11 && (size_stack_a <= consecutive_rrr || // vuelta entera o mas que stackA
                    stackA_size - size_stack_a <= consecutive_rrr) // vuelta entera o mas q stackB
                ){
                    operation[i - 1] += 1;
                    operation[i] = 1;
                    // return;
                }
            }
        }else
            consecutive_rrr = 0;
        i++;
    }
}


void optimice(int *operation, int stackA_size){
    int changed = 1;
    int p_incorrect = 0;

    while (changed){
        changed = 0;
        changed += optimiced_sa(operation, stackA_size);
        changed += optimiced_ra(operation, stackA_size);
        changed += optimiced_rra(operation, stackA_size);
        changed += optimiced_pb(operation, stackA_size);
        changed += optimiced_pa(operation, stackA_size);
        //changed += optimiced_p(operation);
        changed += optimiced_sb(operation);
        changed += optimiced_rb(operation);
        changed += optimiced_rrb(operation);
        changed += optimiced_ss(operation, stackA_size);
        changed += optimiced_rr(operation, stackA_size);
    }

    if (p_incorrect)
        printf("la siguiente tiene los p incorrectos: ");

    optimiced_rrr(operation, stackA_size);
}