# 3.1
## serial

looking at the profiler it can be seen that the algorithm was spedning over 50% of time in the below lines
'''
    for(int j = 0; j < m; j++){
        for(int i = 0; i < n; i++){
            num_in_state[current_grid[i*m +j]]++;
        }
    }
'''
simply changing the double forloop to a single forloop and using some modulus magic the i and j indexes can be found.
But i*m +j is simply calculating the index if the grid was single dimension array. So changing it from a double forloop to a single forloop means
that index can simple be used. 

'''
    for(int k = 0; k < n*m; k++){
        num_in_state[current_grid[k]]++;
 
    }
'''
Now game_of_life is where the bulk of the changes were made, the original code had alot of superfluous sections. Finding the nieghbours was written in a very verbose many to make it obvious what is happening, but it is largly unneeded. Simply defining directions like below accomplishes the same thing

'''
int left = j - 1;
int right = j  + 1;
int up = i - 1;
int down = i + 1;
'''
This works well with the next change which is the prunning of branches in the code. 
looking at the code below
//             if(n_i[0] >= 0 && n_j[0] >= 0 && current_grid[n_i[0] * m + n_j[0]] == ALIVE) neighbours++;
//             if(n_i[1] >= 0 && current_grid[n_i[1] * m + n_j[1]] == ALIVE) neighbours++;
//             if(n_i[2] >= 0 && n_j[2] < m && current_grid[n_i[2] * m + n_j[2]] == ALIVE) neighbours++;
//             if(n_j[3] < m && current_grid[n_i[3] * m + n_j[3]] == ALIVE) neighbours++;
//             if(n_i[4] < n && n_j[4] < m && current_grid[n_i[4] * m + n_j[4]] == ALIVE) neighbours++;
//             if(n_i[5] < n && current_grid[n_i[5] * m + n_j[5]] == ALIVE) neighbours++;
//             if(n_i[6] < n && n_j[6] >= 0 && current_grid[n_i[6] * m + n_j[6]] == ALIVE) neighbours++;
//             if(n_j[7] >= 0 && current_grid[n_i[7] * m + n_j[7]] == ALIVE) neighbours++;
It can be seen to be clean code that checks for boundry conditions. However it can be written in a more verbose and unclean way for the sake of performance. The bulk of the conditions are to check for boundry conditions, however this is only needed when the cell in quesiton is in the border of the grid i.e. i == 0, j == 0, i == n-1, j == m-1. So majority of the time those boundry conditions are checked for no reason. chaning this to one big if statement checking for boundires will mean only 4 conditions are checked for the 8 neighbours. More prunning can be done however, looking at the boundry conditions it can be seen that some repeats and some are redundant. "n_1[n] >=0" is checking if the neighbours above are in the grid, and conversly "n_1[n] < n" is checking if the lower neighbours are in the grid, these cannot happen simultaneously so this can be an if else statement. Even more prunning can happen looking below
//             if(current_grid[i*m + j] == ALIVE && (neighbours == 2 || neighbours == 3)){
//                 next_grid[i*m + j] = ALIVE;  // Cell remains alive
//             } else if(current_grid[i*m + j] == DEAD && neighbours == 3){
//                 next_grid[i*m + j] = ALIVE;  // Cell becomes alive
//             } else {
//                 next_grid[i*m + j] = DEAD;  // Cell dies
//             }

it can be seen that the if and the else if can be combined to one statement and the else statement also sets the cell equal to dead even when the cell was already dead. For larger grid sizes cache misses could happen when accessing memory, so having an if staement to check if the cell is alive before setting it to dead is worth while. 

Apart from prunning, other optimisations were also made. Mainly changing the double forloop to a single forloop and calculating i and j. This was because the profiler said that the code was spending alot of time here. But this works out well because the double forloop calculated the current cell position in the one dimensional grid. So all of these could be replaced with the current index of the loop.

Doing all of these changes decreased the time from 54 seconds down to 9 seconds at a m and n size of 10000 and 10 iterations. Where the pre serial was doing around 5 seconds per iteration ignoring the first iteration. And the optimised serial version was doing around 0.85 seconds per iterantions

The profiler now is saying 
 27.01      2.52     2.52                             game_of_life (01_gol_cpu_serial.c:59 @ 16ab)
 21.86      4.55     2.04                             game_of_life (01_gol_cpu_serial.c:54 @ 16a3)
  9.24      5.41     0.86                             game_of_life_stats (01_gol_cpu_serial.c:127 @ 18f5)
  7.20      6.08     0.67                             game_of_life (01_gol_cpu_serial.c:53 @ 168b)
where the coresponding code is below.
59        if(i > 0 && j > 0 && i < n-1 && j < m-1){
54        i = k/m;
127       for(int k = 0; k < n*m; k++){
53        for(int k = 0; k < n*m; k++){
The bottle necks is the main if statement checking if its not a boundry cell and division, the loops themselves are also causing a bottleneck. Seeing this is it is probably safe to say that the code is very optimised in terms of serial performance. 
## post-serial
doing the same trick to the game_of_life function redu0ced the runtime down to ~4 seconds as 

## post-post-serial
