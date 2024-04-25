#include "common.h"

void game_of_life(struct Options *opt, int *current_grid, int *next_grid, int n, int m){
    int neighbours, i, j;  // Variable to store the number of live neighbors
    int n_i[8], n_j[8];  // Arrays to store row and column indices of neighbors
    
    for(int k = 0; k < n*m; k++){
        i = k/m;
        j = k%m;
        neighbours = 0;  // Reset the neighbor count for each cell
            
        // Define the row and column indices of the 8 neighboring cells
        n_i[0] = i - 1; n_j[0] = j - 1;
        n_i[1] = i - 1; n_j[1] = j;
        n_i[2] = i - 1; n_j[2] = j + 1;
        n_i[3] = i;     n_j[3] = j + 1;
        n_i[4] = i + 1; n_j[4] = j + 1;
        n_i[5] = i + 1; n_j[5] = j;
        n_i[6] = i + 1; n_j[6] = j - 1;
        n_i[7] = i;     n_j[7] = j - 1;


        
        // Apply rules of the Game of Life to update the next state of the current cell
        if(i > 0 && j > 0 && i < n-1 && j < m-1){

            if(current_grid[k-m-1] == ALIVE) neighbours++;
            if(current_grid[k-m] == ALIVE) neighbours++;
            if(current_grid[k-m+1] == ALIVE) neighbours++;
            if(current_grid[k-1] == ALIVE) neighbours++;
            if(current_grid[k+1] == ALIVE) neighbours++;
            if(current_grid[k+m-1] == ALIVE) neighbours++;
            if(current_grid[k+m] == ALIVE) neighbours++;
            if(current_grid[k+m+1] == ALIVE) neighbours++;

        }
        else{
            // Check each neighbor's status and count live neighbors
            if(n_i[0] >= 0 && n_j[0] >= 0 && current_grid[k-m-1] == ALIVE) neighbours++;
            if(n_i[1] >= 0 && current_grid[k-m] == ALIVE) neighbours++;
            if(n_i[2] >= 0 && n_j[2] < m && current_grid[k-m+1] == ALIVE) neighbours++;
            if(n_j[3] < m && current_grid[k+1] == ALIVE) neighbours++;
            if(n_i[4] < n && n_j[4] < m && current_grid[k+m+1] == ALIVE) neighbours++;
            if(n_i[5] < n && current_grid[k+m] == ALIVE) neighbours++;
            if(n_i[6] < n && n_j[6] >= 0 && current_grid[k+m-1] == ALIVE) neighbours++;
            if(n_j[7] >= 0 && current_grid[k-1] == ALIVE) neighbours++;
        }


        if(current_grid[k] == ALIVE && (neighbours == 2 || neighbours == 3)){
            next_grid[k] = ALIVE;  // Cell remains alive
        } else if(current_grid[k] == DEAD && neighbours == 3){
            next_grid[k] = ALIVE;  // Cell becomes alive
        } else {
            next_grid[k] = DEAD;  // Cell dies
        }
    }
    // // Loop through each cell in the grid
    // for(int j = 0; j < m; j++){
    //     for(int i = 0; i < n; i++){
    //         // count the number of neighbours, clockwise around the current cell.
    //         neighbours = 0;  // Reset the neighbor count for each cell
            
    //         // Define the row and column indices of the 8 neighboring cells
    //         n_i[0] = i - 1; n_j[0] = j - 1;
    //         n_i[1] = i - 1; n_j[1] = j;
    //         n_i[2] = i - 1; n_j[2] = j + 1;
    //         n_i[3] = i;     n_j[3] = j + 1;
    //         n_i[4] = i + 1; n_j[4] = j + 1;
    //         n_i[5] = i + 1; n_j[5] = j;
    //         n_i[6] = i + 1; n_j[6] = j - 1;
    //         n_i[7] = i;     n_j[7] = j - 1;

    //         // Check each neighbor's status and count live neighbors
    //         if(n_i[0] >= 0 && n_j[0] >= 0 && current_grid[n_i[0] * m + n_j[0]] == ALIVE) neighbours++;
    //         if(n_i[1] >= 0 && current_grid[n_i[1] * m + n_j[1]] == ALIVE) neighbours++;
    //         if(n_i[2] >= 0 && n_j[2] < m && current_grid[n_i[2] * m + n_j[2]] == ALIVE) neighbours++;
    //         if(n_j[3] < m && current_grid[n_i[3] * m + n_j[3]] == ALIVE) neighbours++;
    //         if(n_i[4] < n && n_j[4] < m && current_grid[n_i[4] * m + n_j[4]] == ALIVE) neighbours++;
    //         if(n_i[5] < n && current_grid[n_i[5] * m + n_j[5]] == ALIVE) neighbours++;
    //         if(n_i[6] < n && n_j[6] >= 0 && current_grid[n_i[6] * m + n_j[6]] == ALIVE) neighbours++;
    //         if(n_j[7] >= 0 && current_grid[n_i[7] * m + n_j[7]] == ALIVE) neighbours++;

    //         // Apply rules of the Game of Life to update the next state of the current cell
    //         if(current_grid[i*m + j] == ALIVE && (neighbours == 2 || neighbours == 3)){
    //             next_grid[i*m + j] = ALIVE;  // Cell remains alive
    //         } else if(current_grid[i*m + j] == DEAD && neighbours == 3){
    //             next_grid[i*m + j] = ALIVE;  // Cell becomes alive
    //         } else {
    //             next_grid[i*m + j] = DEAD;  // Cell dies
    //         }
    //     }
    // }
}

void game_of_life_stats(struct Options *opt, int step, int *current_grid){
    unsigned long long num_in_state[NUMSTATES];
    int m = opt->m, n = opt->n, i, j;
    for(int i = 0; i < NUMSTATES; i++) num_in_state[i] = 0;
    // for(int j = 0; j < m; j++){
    //     for(int i = 0; i < n; i++){
    //         num_in_state[current_grid[i*m + j]]++;
    //     }
    // }
    for(int k = 0; k < n*m; k++){
        i = k/m;
        j = k%m;
        num_in_state[current_grid[i*m+j]]++;
 
    }
    double frac, ntot = opt->m*opt->n;
    FILE *fptr;
    if (step == 0) {
        fptr = fopen(opt->statsfile, "w");
    }
    else {
        fptr = fopen(opt->statsfile, "a");
    }
    fprintf(fptr, "step %d : ", step);
    for(int i = 0; i < NUMSTATES; i++) {
        frac = (double)num_in_state[i]/ntot;
        fprintf(fptr, "Frac in state %d = %f,\t", i, frac);
    }
    fprintf(fptr, " \n");
    fclose(fptr);
}



int main(int argc, char **argv)
{
    struct Options *opt = (struct Options *) malloc(sizeof(struct Options));
    getinput(argc, argv, opt);
    int n = opt->n, m = opt->m, nsteps = opt->nsteps;
    int *grid = (int *) malloc(sizeof(int) * n * m);
    int *updated_grid = (int *) malloc(sizeof(int) * n * m);
    if(!grid || !updated_grid){
        printf("Error while allocating memory.\n");
        return -1;
    }
    int current_step = 0;
    int *tmp = NULL;
    generate_IC(opt->iictype, grid, n, m);
    struct timeval start, steptime;
    start = init_time();
    while(current_step != nsteps){
        steptime = init_time();
        visualise(opt->ivisualisetype, current_step, grid, n, m);
        game_of_life_stats(opt, current_step, grid);
        game_of_life(opt, grid, updated_grid, n, m);
        // swap current and updated grid
        tmp = grid;
        grid = updated_grid;
        updated_grid = tmp;
        current_step++;
        get_elapsed_time(steptime);
    }
    printf("Finnished GOL\n");
    get_elapsed_time(start);
    free(grid);
    free(updated_grid);
    free(opt);
    return 0;
}
