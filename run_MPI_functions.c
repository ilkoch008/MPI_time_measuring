//
// Created by ilya on 03.04.2020.
//

#include "lol.h"

int run_MPI_fun(int length, int iterations, int *sendBuff, int *recvBuff, int *scatterSendBuff) {

    double dtime = 0;
    int size = 0;
    MPI_Status status;
    int numOfProcs, myRank;

    MPI_Comm_size(MPI_COMM_WORLD, &numOfProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    double sum, it, sumForRoot;
    double average, averageForRoot;

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
        if (myRank == 0) {
            sumForRoot += dtime;
        } else {
            sum += dtime;
        }
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
        if (myRank == 0) {
            sumForRoot += dtime;
        } else {
            sum += dtime;
        }
        it++;
    }

    //printf("%d ended\n", myRank);

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

    MPI_Barrier(MPI_COMM_WORLD);

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
        if (myRank == 0) {
            sumForRoot += dtime;
        } else {
            sum += dtime;
        }
        it++;
    }

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

    MPI_Barrier(MPI_COMM_WORLD);

//----------------------------------------------------------------------------------------------------------------------

    it = 0;
    sum = 0;
    sumForRoot = 0;

    while (1) {
        if (it == iterations)
            break;
        dtime = MPI_Wtime();
        MPI_Gather(recvBuff /*sendBuff*/, length, MPI_INT, scatterSendBuff /*recvBuff*/,
                length, MPI_INT, 0, MPI_COMM_WORLD);
        dtime = MPI_Wtime() - dtime;
        //printf("iteration %d; my rank: %d\n", it, myRank);
        if (myRank == 0) {
            sumForRoot += dtime;
        } else {
            sum += dtime;
        }
        it++;
    }

    if (myRank == 0) {
        for (int i = 1; i < numOfProcs; i++) {
            MPI_Recv(&dtime, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            sum += dtime;
        }
        averageForRoot = sumForRoot / iterations;
        average = sum / (iterations * (numOfProcs - 1));
        printf("Average time of MPI_Gather for not root: %f\n", average);
        printf("Average time of MPI_Gather for root:     %f\n", averageForRoot);
//        printf("--------------------------------------------------------------------------------------------\n");
    } else {
        MPI_Send(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

//----------------------------------------------------------------------------------------------------------------------

    return 0;
}