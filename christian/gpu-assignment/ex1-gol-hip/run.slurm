#!/bin/bash --login 
#SBATCH --reservation=CurtinHPCcourse
#SBATCH --account=courses0100-gpu
#SBATCH --tasks=1 
#SBATCH --gpus-per-node=8
#SBATCH --partition=gpu
#SBATCH --time=00:05:00 
#SBATCH --export=NONE
module load rocm/5.2.3

module load rocm/5.2.3

srun hipcc --offload-arch=gfx90a -o add src/game_of_life_hip.cpp
srun ./add
