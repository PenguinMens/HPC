
#define MAXITER 1000
#define N	100
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <mpi.h>
#include <string.h> // For memcpy
#define CHUNKSIZE 10
#define LFW_TAG 1
#define RESULTS_TAG 0
#define WORK_TAG 2
#define STOP_TAG 3
#define EXTRA_TAG 4
/* ----------------------------------------------------------------*/
// function declarations
int doMandlebrot(int loopStart, int loopEnd, float **chunkReturn)
{
    int loop,i,j,k;
    float complex   z, kappa;
    float  *chunkBuff;
    chunkBuff = (float *) malloc((N*N/10)*sizeof(float));
    for (loop=loopStart; loop<loopEnd; loop++) {
    i=loop%N;
    j=loop/N;

    z=kappa= (4.0*(i-N/2))/N + (4.0*(j-N/2))/N * I;

    k=1;
    while ((cabs(z)<=2) && (k++<MAXITER)) 
        z= z*z + kappa;
    
    chunkBuff[loop - loopStart]= log((float)k) / log((float)MAXITER);
    }
    *chunkReturn = chunkBuff;
    return 1;
    
}
    int master(int, float**);
    int slave(int, int);
/* ----------------------------------------------------------------*/



int main(int argc, char *argv[]) {
    int          i,rank,num,ncpu,tag,buff, flag,chunkSize, temp,green,blue;
    float *x;
    FILE   *fp;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&ncpu);
    chunkSize = CHUNKSIZE;
    
    if(argc > 1){
        chunkSize=atoi(argv[1]);
    }
    
    if(ncpu < 2){
        printf("needs atleast 2 processor");
        MPI_Finalize();
        return 0;
    }
 
    if (rank==0) {
        master(chunkSize, &x);

    }
    else if (rank!=0) {
        slave(rank, chunkSize);
    }
    if(rank == 0){
        printf("Writing mandelbrot2.ppm %d\n", rank);
        fp = fopen ("mandelbrot2.ppm", "w");
        fprintf (fp, "P3\n%4d %4d\n255\n", N, N);

        for (int loop=0; loop<N*N; loop++) 
            if (x[loop]<0.5) {
                green= (int) (2*x[loop]*255);
                    fprintf (fp, "%3d\n%3d\n%3d\n", 255-green,green,0);
            } else {
                blue= (int) (2*x[loop]*255-255);
                    fprintf (fp, "%3d\n%3d\n%3d\n", 0,255-blue,blue);
            }
            fclose(fp);
    }
    else
    {
        printf("finished %d\n", rank);
    }
    //free(x);
    MPI_Finalize();
    return 0;
}
int master(int chunkSize, float **returnMandlebrot) {
    MPI_Status status, status2;
    int counter = 0;
    int i,recievedAmount, num, ncpu,temp,flag,commands[2], stop, tag;
    float *x;
    float *chunk;
    recievedAmount = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &ncpu);
    int isWorking[ncpu];
    x=(float *) malloc(N*N*sizeof(float));
    chunk = (float *) malloc((chunkSize)*sizeof(float));

    for(i = 1; i< ncpu; i++){
        isWorking[i] = 1;
        //printf("sending work iteration %d\n", counter);
        
        if(counter >= N*N)
        {
            printf("breaking rank %d\n", i);
             MPI_Send(&counter, 1, MPI_INT, i, STOP_TAG, MPI_COMM_WORLD);
        } 
        else
        {
               printf("sending work to workder %d at %d\n", i, counter);
            MPI_Send(&counter, 1, MPI_INT, i, WORK_TAG, MPI_COMM_WORLD);
            counter = counter + chunkSize;
        }
   

    }
    while(recievedAmount < N*N) { 
        printf("is recieved %d",recievedAmount <= N*N);
        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status2);

        if(status2.MPI_TAG == EXTRA_TAG) {
            //MPI_Recv(&num, 1, MPI_INT, status2.MPI_SOURCE, status2.MPI_TAG, MPI_COMM_WORLD, &status);
            // printf("receiving results\n");
            // printf("commands: %d, %d\n", commands[0], commands[1]);
            MPI_Recv(&num, 1,MPI_INT, status2.MPI_SOURCE, EXTRA_TAG, MPI_COMM_WORLD, &status);
            stop = num + chunkSize; 
            if(stop >= N*N)
            {
                stop = N*N;
            }
    
            MPI_Recv(&x[num], stop - num,MPI_FLOAT, status2.MPI_SOURCE, RESULTS_TAG, MPI_COMM_WORLD, &status);
            recievedAmount = recievedAmount + (stop - num);
            printf("recieved amount %d\n", recievedAmount);
            if(counter >= N*N)
            {
               printf("breaking rank %d\n", i); 
               tag = STOP_TAG;
            }
            else
            {
                printf("sending work to workder %d at %d\n", status2.MPI_SOURCE, counter);
                tag = WORK_TAG;
            }
             MPI_Send(&counter, 1, MPI_INT, status2.MPI_SOURCE, tag, MPI_COMM_WORLD);
             counter = counter + chunkSize;
            //printf("commands: %d, %d\n", commands[0], commands[1]);
           // memcpy(,chunk, (commands[1] - commands[0])*sizeof(float));
        }
        

    }
    free(chunk);
    *returnMandlebrot = x;
    return 0;
}
int slave(int rank, int chunkSize) {
    MPI_Status sStatus, sStatus2;
    int counter2 = 0;
    int commands[2];
    float *chunk;
    int start, stop ;
    while(1) {
        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &sStatus);
        if(sStatus.MPI_TAG == WORK_TAG) {
            MPI_Recv(&start, 1, MPI_INT, 0, sStatus.MPI_TAG, MPI_COMM_WORLD, &sStatus2);
            if(start + chunkSize > N*N)
            {
                stop = N*N;
            }
            else
            {
                stop = start + chunkSize;
            }
            doMandlebrot(start, stop, &chunk);
            
            MPI_Send(&start, 1, MPI_INT, 0, EXTRA_TAG, MPI_COMM_WORLD);
            MPI_Send(chunk, stop - start, MPI_FLOAT, 0, RESULTS_TAG, MPI_COMM_WORLD);
            
        } else if(sStatus.MPI_TAG == STOP_TAG) {
            MPI_Recv(&counter2, 1, MPI_INT, 0, STOP_TAG, MPI_COMM_WORLD, &sStatus2);
            break;
        }
    }
    free(chunk);
    return 0;
    
}