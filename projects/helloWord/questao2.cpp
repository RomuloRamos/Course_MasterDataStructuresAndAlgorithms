#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MISSED_SHOT     'X'
#define SUCCESS_SHOT    'O'
#define UNSHOT_PLACE    '.'
#define VERTICAL_ANALYSIS   0
#define HORIZONTAL_ANALYSIS   1

int board_size = 0,amount_ships = 0, distinct_places_possible;
char battleship_board[6][6];
int auxiliary_board[6][6];
int ship_size[6] = {0};

int compare_ints(const void* a, const void* b)      // from cppreference
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
 
    // return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
    // return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
}




bool judge_place(int num, int line, int column, int dir)
{    
    if(dir == VERTICAL_ANALYSIS)
    {    
        for(int i = 0; i < ship_size[num]; i++)
        {    
            if(line+i < 1 || line+i > board_size || column < 1 || column > board_size)
            {    
                return 0;
            }
            if(battleship_board[line+i][column] == MISSED_SHOT || auxiliary_board[line+i][column] == 1)
            {    
                return 0;
            } 
        }
        return 1;
    }
    else    // HORIZONTAL_ANALYSIS
    {    
        for(int i = 0; i < ship_size[num]; i++)
        {    
            if(line < 1 || line > board_size || column+i < 1 || column+i > board_size)
            {    
                return 0;
            }
            if(battleship_board[line][column+i] == MISSED_SHOT || auxiliary_board[line][column+i] == 1)
            {    
                return 0;
            }
        }
        return 1;
    }
}

void inserting_ships(int num, int line, int column, int dir)
{    
    if(dir == VERTICAL_ANALYSIS)
    {   
        for(int i = 0; i < ship_size[num]; i++)
        {
            auxiliary_board[line+i][column] = 1;
        }
    }
    else    // HORIZONTAL_ANALYSIS
    {    
        for(int i = 0; i < ship_size[num]; i++)
        {    
            auxiliary_board[line][column+i]=1;
        }
    }
}

void removing_ships(int num, int line, int column, int dir)
{    
    if(dir == VERTICAL_ANALYSIS)
    {    
        for(int i = 0; i < ship_size[num]; i++)
        {    
            auxiliary_board[line+i][column] = 0;
        }
    }
    else    // HORIZONTAL_ANALYSIS
    {    
        for(int i = 0; i < ship_size[num]; i++)
        {    
            auxiliary_board[line][column+i] = 0;
        }
    }   
}
void calculate_distinct_places(int placed_num)
{    
    if(placed_num > amount_ships)
    {
        for(int line = 1; line <= board_size; line++)
        {    
            for(int column = 1; column <= board_size; column++)
            {    
                if(battleship_board[line][column] == SUCCESS_SHOT && auxiliary_board[line][column] == 0)
                {    
                    return;
                }
            }
        }
        distinct_places_possible++;
        return;
    }
    for(int line = 1; line <= board_size; line++)
    {    
        for(int column = 1; column <= board_size; column++)
        {    
            if(battleship_board[line][column] == MISSED_SHOT || auxiliary_board[line][column] == 1)
            {    
                continue;
            }
            if(judge_place(placed_num, line, column, VERTICAL_ANALYSIS))
            {    
                inserting_ships(placed_num, line, column, VERTICAL_ANALYSIS);
                calculate_distinct_places(placed_num+1);
                removing_ships(placed_num, line, column, VERTICAL_ANALYSIS);
            }
            if(ship_size[placed_num] == 1)
            {    
                continue;
            }
            if(judge_place(placed_num, line, column, HORIZONTAL_ANALYSIS))
            {    
                inserting_ships(placed_num, line, column, HORIZONTAL_ANALYSIS);
                calculate_distinct_places(placed_num+1);
                removing_ships(placed_num, line, column, HORIZONTAL_ANALYSIS);
            }
        }
    }
}

int main()
{    
    scanf("%d%d", &board_size, &amount_ships);        // reading board size and amount ships

    for(int line = 1; line <= board_size; line++)
    {
        scanf("%s", battleship_board[line]+1);             // reading Alice grid
    }

    int ship_size_aux[amount_ships];
 
    for(int size = 0; size < amount_ships; size++)
    {
        scanf("%d", &ship_size_aux[size]);             // reading ship sizes        
    } 
    
    int size = sizeof ship_size_aux / sizeof *ship_size_aux;    

    qsort(ship_size_aux, size, sizeof(int), compare_ints);      // from cppreference

    for (int i = 0; i < amount_ships; i++)
    {
        ship_size[i+1] = ship_size_aux[i];
    }
    calculate_distinct_places(1);       // first ship size
    printf("%d\n", distinct_places_possible);

    return 0;
}