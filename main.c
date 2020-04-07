
#include "lol.h"


int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    double dtime = MPI_Wtime();

    int length;

    int size = 0;
    int *sendBuff;
    int *recvBuff;

    int numOfProcs, myRank, namelen;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    char processor_name[MPI_MAX_PROCESSOR_NAME];

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
    int *scatterSendBuff;
    scatterSendBuff = (int *) malloc(sizeof(int) * length * numOfProcs);

//    printf("My rank is %d and i'm going to receive %d ints\n", myRank, length);

    if (myRank == 0) {
        printf("============================================================================================\n");
    }

    run_MPI_fun(length, iterations, sendBuff, recvBuff, scatterSendBuff);

    if (myRank == 0) {
        printf("============================================================================================\n");
    }

    run_my_fun(length, iterations, sendBuff, recvBuff, scatterSendBuff);

    MPI_Barrier(MPI_COMM_WORLD);
    free(recvBuff);
    free(sendBuff);
    free(scatterSendBuff);
    MPI_Finalize();
    return 0;
}
