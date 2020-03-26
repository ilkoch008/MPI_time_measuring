#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    double dtime = MPI_Wtime();

    int length;

    int size = 0;
    int *sendBuff;
    int *recvBuff;

    int numOfProcs, myRank, namelen;
    double accuracy;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    accuracy = MPI_Wtick();

    MPI_Comm_size(MPI_COMM_WORLD, &numOfProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Get_processor_name(processor_name, &namelen);

    dtime = MPI_Wtime() - dtime;
    int iterations;

    if (myRank == 0) {
        printf("Enter number of elements in sendBuff to operate\n");
        scanf("%d", &length);
        printf("Enter the number of iterations\n");
        scanf("%d", &iterations);
        for (int i = 1; i < numOfProcs; i++) {
            MPI_Send(&length, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&iterations, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(&length, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        MPI_Recv(&iterations, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    }


    sendBuff = (int *) malloc(sizeof(int) * length);
    recvBuff = (int *) malloc(sizeof(int) * length);
    int * scatterSendBuff;
    scatterSendBuff = (int *) malloc(sizeof(int) * length * numOfProcs);

//    printf("My rank is %d and i'm going to receive %d ints\n", myRank, length);

    double sum, it, sumForRoot;
    double average, averageForRoot;
    if(myRank == 0) {
        printf("--------------------------------------------------------------------------------------------\n");
    }

//----------------------------------------------------------------------------------------------------------------------

    it = 0;
    sum = 0;
    sumForRoot = 0;

    while (1) {
        if (it == iterations)
            break;
        dtime = MPI_Wtime();
        MPI_Bcast(sendBuff, length, MPI_INT, 0, MPI_COMM_WORLD);
        dtime = MPI_Wtime() - dtime;
        //printf("iteration %d; my rank: %d\n", it, myRank);
        if(myRank == 0){
            sumForRoot += dtime;
        } else {
            sum += dtime;
        }
        MPI_Barrier(MPI_COMM_WORLD);
        it++;
    }

    if (myRank == 0) {
        for (int i = 1; i < numOfProcs; i++) {
            MPI_Recv(&dtime, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            sum += dtime;
        }
        averageForRoot = sumForRoot / iterations;
        average = sum / (iterations * (numOfProcs - 1));
        printf("Average time of MPI_Bcast for not root: %f\n", average);
        printf("Average time of MPI_Bcast for root:     %f\n", averageForRoot);
        printf("--------------------------------------------------------------------------------------------\n");
    } else {
        MPI_Send(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);


//----------------------------------------------------------------------------------------------------------------------

    it = 0;
    sum = 0;
    sumForRoot = 0;

    while (1) {
        if (it == iterations)
            break;
        dtime = MPI_Wtime();
        MPI_Reduce(sendBuff, recvBuff, length, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        dtime = MPI_Wtime() - dtime;
        //printf("iteration %d; my rank: %d\n", it, myRank);
        if(myRank == 0){
            sumForRoot += dtime;
        } else {
            sum += dtime;
        }
        MPI_Barrier(MPI_COMM_WORLD);
        it++;
    }

    //printf("%d ended\n", myRank);

    sum += dtime;
    if (myRank == 0) {
        for (int i = 1; i < numOfProcs; i++) {
            MPI_Recv(&dtime, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            sum += dtime;
        }
        averageForRoot = sumForRoot / iterations;
        average = sum / (iterations * (numOfProcs - 1));
        printf("Average time of MPI_Reduce for MPI_SUM for not root: %f\n", average);
        printf("Average time of MPI_Reduce for MPI_SUM for root:     %f\n", averageForRoot);
        printf("--------------------------------------------------------------------------------------------\n");
    } else {
        MPI_Send(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

//----------------------------------------------------------------------------------------------------------------------

    it = 0;
    sum = 0;
    sumForRoot = 0;

    while (1) {
        if (it == iterations)
            break;
        dtime = MPI_Wtime();
        MPI_Scatter(scatterSendBuff, length, MPI_INT, recvBuff, length, MPI_INT, 0, MPI_COMM_WORLD);
        dtime = MPI_Wtime() - dtime;
        //printf("iteration %d; my rank: %d\n", it, myRank);
        if(myRank == 0){
            sumForRoot += dtime;
        } else {
            sum += dtime;
        }
        MPI_Barrier(MPI_COMM_WORLD);
        it++;
    }

    sum += dtime;
    if (myRank == 0) {
        for (int i = 1; i < numOfProcs; i++) {
            MPI_Recv(&dtime, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            sum += dtime;
        }
        averageForRoot = sumForRoot / iterations;
        average = sum / (iterations * (numOfProcs - 1));
        printf("Average time of MPI_Scatter for not root: %f\n", average);
        printf("Average time of MPI_Scatter for root:     %f\n", averageForRoot);
        printf("--------------------------------------------------------------------------------------------\n");
    } else {
        MPI_Send(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

//----------------------------------------------------------------------------------------------------------------------

    it = 0;
    sum = 0;
    sumForRoot = 0;

    while (1) {
        if (it == iterations)
            break;
        dtime = MPI_Wtime();
        MPI_Gather(recvBuff, length, MPI_INT, scatterSendBuff, length, MPI_INT, 0, MPI_COMM_WORLD);
        dtime = MPI_Wtime() - dtime;
        //printf("iteration %d; my rank: %d\n", it, myRank);
        if(myRank == 0){
            sumForRoot += dtime;
        } else {
            sum += dtime;
        }
        MPI_Barrier(MPI_COMM_WORLD);
        it++;
    }

    sum += dtime;
    if (myRank == 0) {
        for (int i = 1; i < numOfProcs; i++) {
            MPI_Recv(&dtime, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            sum += dtime;
        }
        averageForRoot = sumForRoot / iterations;
        average = sum / (iterations * (numOfProcs - 1));
        printf("Average time of MPI_Gather for not root: %f\n", average);
        printf("Average time of MPI_Gather for root:     %f\n", averageForRoot);
        printf("--------------------------------------------------------------------------------------------\n");
    } else {
        MPI_Send(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

//----------------------------------------------------------------------------------------------------------------------


    MPI_Barrier(MPI_COMM_WORLD);
    free(recvBuff);
    free(sendBuff);
    MPI_Finalize();
    return 0;
}
