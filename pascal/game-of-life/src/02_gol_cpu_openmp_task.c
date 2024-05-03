#include "common.h"



void game_of_life(struct Options *opt, int *current_grid, int *next_grid, int n, int m){

    // get rid of the double forloops and use a single for loop
    #pragma omp parallel  
        #pragma omp single
        #pragma omp taskloop  default(none) shared(n,m,current_grid,next_grid)
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    int k = i*m + j;
                    int neighbours = 0; 
                     // Reset the neighbor count for each cell
                    
                    // we dont need boundry checking if its in the inner grid
                    if(i > 0 && j > 0 && i < n-1 && j < m-1){
                        // we can directly use k and m to get neighbours
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
                        // define direction relative to the current cell
                        // diagonals are a combination of 2 directions
                        int left = j - 1;
                        int right = j  + 1;
                        int up = i - 1;
                        int down = i + 1;
                        // Check each neighbor's status and count live neighbors
                        // having this gernal check actaully decrease the number of conditions from 12 to 8
                        if(up >= 0){
                            // checks upper boundry
                            if(left >= 0 && current_grid[k-m-1] == ALIVE) neighbours++;
                            if(current_grid[k-m] == ALIVE) neighbours++;
                            if(right < m && current_grid[k-m+1] == ALIVE) neighbours++;
                        }
                        if(down < n){   // checks lower bounder
                            if(right< m && current_grid[k+m+1] == ALIVE) neighbours++;
                            if(current_grid[k+m] == ALIVE) neighbours++;
                            if(left>= 0 && current_grid[k+m-1] == ALIVE) neighbours++;
                        }

                        if(right < m && current_grid[k+1] == ALIVE) neighbours++;
                        if(left >= 0 && current_grid[k-1] == ALIVE) neighbours++;
                    }


                    // store variable because memmory retrieval could be costly
                    int state;
                    state = current_grid[k];
                    //dont know if doing this reduces branching but it feels liek ti does
                    if(state == ALIVE && (neighbours == 2 || neighbours == 3)){
                            next_grid[k] = ALIVE;  // Cell remains alive            
                    } else if(state == DEAD && neighbours == 3){
                            next_grid[k] = ALIVE;  // Cell remains alive
                    } else {
                        next_grid[k] = DEAD;  // Cell dies 
                    }               
                }
            }
}

void game_of_life_stats(struct Options *opt, int step, int *current_grid){
    unsigned long long num_in_state[NUMSTATES];
    int m = opt->m, n = opt->n, i, j;
    for(int i = 0; i < NUMSTATES; i++) num_in_state[i] = 0;

    #pragma omp parallel  default(none) shared(current_grid, n, m,num_in_state)
    #pragma omp single    
    #pragma omp taskloop reduction (+:num_in_state) 
    for(int k = 0; k < n*m; k++){
        // the orignal was i*m+j which is essentailly
        // finding the index in a 1 d array. 
        // could just set it to a 1d array
        num_in_state[current_grid[k]]++;
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
