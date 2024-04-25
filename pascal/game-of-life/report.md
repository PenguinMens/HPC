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
simply changing the double forloop to a single forloop and using some modulus magic the i and j indexes can be found

'''
    for(int k = 0; k < n*m; k++){
        i = k/m;
        j = k%m;
        num_in_state[current_grid[i*m+j]]++;
 
    }
'''
This rereduced the run speed by 66% from 30s to ~10 seoncds

## post-serial
doing the same trick to the game_of_life function redu0ced the runtime down to ~4 seconds

## post-post-serial
