#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define NON_RESIDENTIAL_SECTOR	'.'
#define RESIDENTIAL_SECTOR	'R'
#define GODZILLA_START	'G'
#define GODZILLA_MOVED	'X'
#define MECH_POSITION	'M'

int number_of_tests_cases = 0, map_length = 0, map_width = 0, residential_destroyed = 0;
char initial_grid[1000][1000] = {0}; 
char godzilla_visited_grid[1000][1000] = {0}; 
int godzilla_position_x = -1, godzilla_position_y = -1, amount_mech = 0;
bool godzilla_neutralized = false;
int mech_unit_position[100][2] = {0};


void goodzilla_move()
{
    if (godzilla_position_x - 1 >= 0 &&         // valid position, to move up we need to subtract from x
        initial_grid[godzilla_position_x-1][godzilla_position_y] == RESIDENTIAL_SECTOR &&   // residential position
        godzilla_visited_grid[godzilla_position_x-1][godzilla_position_y] == 0)     // not visited yet
    {
        residential_destroyed++;
        initial_grid[godzilla_position_x-1][godzilla_position_y] = NON_RESIDENTIAL_SECTOR;
        godzilla_visited_grid[godzilla_position_x-1][godzilla_position_y] = GODZILLA_MOVED;
        godzilla_position_x--;
        return;
    } 
    else if (godzilla_position_y - 1 >= 0 &&    // valid position, to move left we need to subtract from y
        initial_grid[godzilla_position_x][godzilla_position_y-1] == RESIDENTIAL_SECTOR &&   // residential position
        godzilla_visited_grid[godzilla_position_x][godzilla_position_y-1] == 0)     // not visited yet
    {
        residential_destroyed++;
        initial_grid[godzilla_position_x][godzilla_position_y-1] = NON_RESIDENTIAL_SECTOR;
        godzilla_visited_grid[godzilla_position_x][godzilla_position_y-1] = GODZILLA_MOVED;
        godzilla_position_y--;
        return;
    } 
    else if (godzilla_position_x + 1 < map_width &&     // valid position, to move down we need to add to x
        initial_grid[godzilla_position_x+1][godzilla_position_y] == RESIDENTIAL_SECTOR &&   // residential position
        godzilla_visited_grid[godzilla_position_x+1][godzilla_position_y] == 0)     // not visited yet
    {
        residential_destroyed++;
        initial_grid[godzilla_position_x+1][godzilla_position_y] = NON_RESIDENTIAL_SECTOR;
        godzilla_visited_grid[godzilla_position_x+1][godzilla_position_y] = GODZILLA_MOVED;
        godzilla_position_x++;
        return;
    } 
    else if (godzilla_position_y + 1 < map_length &&     // valid position, to move right we need to add to y
        initial_grid[godzilla_position_x][godzilla_position_y+1] == RESIDENTIAL_SECTOR &&   // residential position
        godzilla_visited_grid[godzilla_position_x][godzilla_position_y+1] == 0)     // not visited yet
    {
        residential_destroyed++;
        initial_grid[godzilla_position_x][godzilla_position_y+1] = NON_RESIDENTIAL_SECTOR;
        godzilla_visited_grid[godzilla_position_x][godzilla_position_y+1] = GODZILLA_MOVED;
        godzilla_position_y++;
        return;
    } 
    else if (godzilla_position_x - 1 >= 0)
    {
        godzilla_visited_grid[godzilla_position_x-1][godzilla_position_y] = GODZILLA_MOVED;
        godzilla_position_x--;  // moving to the north
        return;
    }
    else
    {
        return; // should never reach here
    }
}


void check_if_possible_shoot(int mech)
{
    int mech_position_x = mech_unit_position[mech][0];
    int mech_position_y = mech_unit_position[mech][1];

    if (mech_position_x == godzilla_position_x && mech_position_y == godzilla_position_y){
        godzilla_neutralized = true;
        printf("%d\n", residential_destroyed);
        return;
    } 
    else if (mech_position_x == godzilla_position_x)
    {        
        
        for (int begin = mech_position_y+1; begin < godzilla_position_y; begin++)    // check no residentials between mech and godzilla
        {
            if (initial_grid[mech_position_x][begin] != RESIDENTIAL_SECTOR)
            {
                continue;
            }
            else
            {
                godzilla_neutralized = false;
                return;
            }
        }
        godzilla_neutralized = true;
        printf("%d\n", residential_destroyed);
        return;
    }
    else if (mech_position_y == godzilla_position_y)
    {
        for (int begin = mech_position_x+1; begin < godzilla_position_x; begin++)    // check no residentials between mech and godzilla
        {
            if (initial_grid[begin][mech_position_y] != RESIDENTIAL_SECTOR)
            {
                continue;
            }
            else
            {
                godzilla_neutralized = false;
                return;
            }
        }
        godzilla_neutralized = true;
        printf("%d\n", residential_destroyed);
        return;
    }
    return;
}

void mech_move()
{
    for(int mech = 0; mech < amount_mech; mech++)
    {
        int mech_position_x = mech_unit_position[mech][0];
        int mech_position_y = mech_unit_position[mech][1];

        if (mech_position_x - 1 >= 0 &&         // valid position, to move up we need to subtract from x
            initial_grid[mech_position_x-1][mech_position_y] != RESIDENTIAL_SECTOR)     
        {
            mech_position_x--;
            mech_unit_position[mech][0] = mech_unit_position[mech][0] - 1;
        } 
        else if (mech_position_y - 1 >= 0 &&         // valid position, to move left we need to subtract from y
            initial_grid[mech_position_x][mech_position_y-1] != RESIDENTIAL_SECTOR)     
        {
            mech_position_y--;
            mech_unit_position[mech][1] = mech_unit_position[mech][1] - 1;
        } 
        else if (mech_position_x + 1 < map_width &&         // valid position, to move down we need to add to x
            initial_grid[mech_position_x+1][mech_position_y] != RESIDENTIAL_SECTOR)     
        {
            mech_position_x++;
            mech_unit_position[mech][0] = mech_unit_position[mech][0] + 1;
        } 
        else if (mech_position_y + 1 < map_length &&         // valid position, to move right we need to add to y
            initial_grid[mech_position_x][mech_position_y+1] != RESIDENTIAL_SECTOR)     
        {
            mech_position_y++;
            mech_unit_position[mech][1] = mech_unit_position[mech][1] + 1;
        }         
        else
        {
            continue; // should never reach here
        }
        check_if_possible_shoot(mech);
        if (godzilla_neutralized == true)
        {            
            return;
        }
    }
}

void calculate_residentials_affected()
{   
    while(!godzilla_neutralized){
        goodzilla_move();
        mech_move();        
    }
    return;
}


void check_godzilla_and_mech_position(int line)
{
    for(int column = 0; column < map_length; column++){

        if(initial_grid[line][column] == GODZILLA_START && godzilla_position_x == -1 && godzilla_position_y == -1)
        {
            godzilla_position_x = line;
            godzilla_position_y = column;
            godzilla_visited_grid[godzilla_position_x][godzilla_position_y] = GODZILLA_MOVED;
        }

        if(initial_grid[line][column] == MECH_POSITION)     
        {
            mech_unit_position[amount_mech][0] = line;      // position x of the # mech
            mech_unit_position[amount_mech][1] = column;    // position y of the # mech
            amount_mech++;              // checking amout mech per line
        }
    }
    return;
}   

int main ()
{   int test_case = 0;
    scanf("%d", &number_of_tests_cases);
    while(test_case < number_of_tests_cases)
    {
    	scanf("%d%d", &map_length, &map_width);

    	for(int line = 0; line < map_width; line++)
	    {
	        scanf("%s", initial_grid[line]);
            check_godzilla_and_mech_position(line);           
	    }
        calculate_residentials_affected();         

        godzilla_position_x = -1;
        godzilla_position_y = -1;
        map_length = 0;
        map_width = 0;
        godzilla_neutralized = false;
        residential_destroyed = 0;
        amount_mech = 0;

    	test_case++;
    }    
    return 0;
}
