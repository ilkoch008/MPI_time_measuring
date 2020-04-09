//
// Created by ilya on 07.04.2020.
//
#include <assert.h>
#include "lol.h"

int test_my_functions(int func_for_testing){

    int size_of_buff;
    int size_of_big_buff;
    int size = 0;

    int numOfProcs, myRank, namelen;
    int numOfProcsFromFile;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Comm_size(MPI_COMM_WORLD, &numOfProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Get_processor_name(processor_name, &namelen);
    int root;

    if(myRank == 0){
        FILE* file = fopen("test1.txt", "r");
        char str[10000];
        for(int i = 0; i < 10000; i++){
            fscanf(file, "%c", (str + i));
            if(*(str + i) == EOF){
                break;
            }
        }

        char *endptr = strstr(str, "number of el");
        numOfProcsFromFile = (int) strtol(strstr(str, "):") + 2, &endptr, 10);
        if(numOfProcs != numOfProcsFromFile){
            fprintf(stderr, "Number of processes doesn't match the quantity pointed in file!\n");
        }
        endptr = strstr(str, "root:");
        size_of_buff = (int) strtol(strstr(str, "buffer:") + 7, &endptr, 10);
        endptr = strstr(str, "elements in buffers");
        root = (int) strtol(strstr(str, "root:") + 5, &endptr, 10);
        MPI_Bcast(&size_of_buff, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);
        fclose(file);
    } else {
        MPI_Bcast(&size_of_buff, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }


    MPI_Barrier(MPI_COMM_WORLD);

    FILE* file = fopen("test1.txt", "r");
    char str[10000];
    for(int i = 0; i < 10000; i++){
        fscanf(file, "%c", (str + i));
        if(*(str + i) == EOF){
            break;
        }
    }
    fclose(file);


    char func_for_reduce[20];
    strncpy(func_for_reduce, strstr(str, "function for my_Reduce: ") + 24,
            (int) (strstr(str, "elements in buffers for each process:") - 24 - strstr(str, "function for my_Reduce: ")));
//    if(myRank == 0){
//        printf("%s\n", func_for_reduce);
//    }
    MPI_Op op_for_reduce = define_func_for_reduce(func_for_reduce);

    size_of_big_buff = numOfProcs * size_of_buff;
    int * buff = malloc(size_of_buff * sizeof(int));
    int * big_buff = malloc(size_of_big_buff * sizeof(int));

    char * nptr = strstr(str, "elements in buffers for each process:") + 37;
    char * endptr;
    for (int i = 0; i < myRank; i++){
        nptr = strstr(nptr + 1, "\n");
    }
    for (int i = 0; i < size_of_buff; i++){
        endptr = strstr(nptr +  1, " ");
        buff[i] = (int) strtol(nptr, &endptr, 10);
        nptr = endptr;
    }

    nptr = strstr(str, "elements in big buffer (for scatter):") + 37;
    for (int i = 0; i < size_of_big_buff; i++) {
        endptr = strstr(nptr + 1, " ");
        big_buff[i] = (int) strtol(nptr, &endptr, 10);
        nptr = endptr;
    }

//    if(myRank == 0) {
//        for (int i = 0; i < size_of_big_buff; i++) {
//            printf("%d ", big_buff[i]);
//        }
//        printf("\n");
//    }

    int * bcast_expected = malloc(size_of_buff * sizeof(int));
    nptr = strstr(str, "expected for my_Bcast:") + 22;
    for (int i = 0; i < myRank; i++){
        nptr = strstr(nptr + 1, "\n");
    }
    for (int i = 0; i < size_of_buff; i++){
        endptr = strstr(nptr +  1, " ");
        bcast_expected[i] = (int) strtol(nptr, &endptr, 10);
        nptr = endptr;
    }

    int * reduce_expected = malloc(size_of_buff * sizeof(int));
    nptr = strstr(str, "expected for my_Reduce:") + 23;
    for (int i = 0; i < size_of_buff; i++){
        endptr = strstr(nptr +  1, " ");
        reduce_expected[i] = (int) strtol(nptr, &endptr, 10);
        nptr = endptr;
    }

    int * scatter_expected = malloc(size_of_buff * sizeof(int));
    nptr = strstr(str, "expected for my_Scatter:") + 24;
    for (int i = 0; i < myRank; i++){
        nptr = strstr(nptr + 1, "\n");
    }
    for (int i = 0; i < size_of_buff; i++){
        endptr = strstr(nptr +  1, " ");
        scatter_expected[i] = (int) strtol(nptr, &endptr, 10);
        nptr = endptr;
    }

    nptr = strstr(str, "expected for my_Gather:") + 23;
    int *gather_expected = malloc(size_of_big_buff * sizeof(int));
    for (int i = 0; i < size_of_big_buff; i++) {
        endptr = strstr(nptr + 1, " ");
        gather_expected[i] = (int) strtol(nptr, &endptr, 10);
        nptr = endptr;
    }

    int * recvbuf = malloc(size_of_buff * sizeof(int));
    int num_of_wrong_results = 0;

    MPI_Barrier(MPI_COMM_WORLD);

    switch (func_for_testing){
        case MY_BROADCAST:
            if(myRank == 0) {
                printf("testing my_Bcast\n");
                fflush(stdout);
            }
            my_Bcast(buff, size_of_buff, MPI_INT, root, MPI_COMM_WORLD);
            for(int i = 0; i < size_of_buff; i++){
                if(buff[i] != bcast_expected[i]){
                    num_of_wrong_results++;
                }
            }
            if(num_of_wrong_results != 0){
                printf(ANSI_COLOR_RED"my rank = %d; %d wrong results for my_Bcast" ANSI_COLOR_RESET "\n", myRank, num_of_wrong_results);
                fflush(stdout);
            } else {
                printf(ANSI_COLOR_GREEN   "myRank = %d, my_Bcast is OK"   ANSI_COLOR_RESET "\n", myRank);
                fflush(stdout);
            }
            break;
        case MY_GATHER:
            if(myRank == 0) {
                printf("testing my_Gather\n");
                fflush(stdout);
            }
            my_Gather(buff, size_of_buff, MPI_INT, big_buff, size_of_buff, MPI_INT, root, MPI_COMM_WORLD);
            if(myRank == root) {
                for (int i = 0; i < size_of_big_buff; i++) {
                    if (big_buff[i] != gather_expected[i]) {
                        num_of_wrong_results++;
                    }
                }
                if (num_of_wrong_results != 0) {
                    printf(ANSI_COLOR_RED "myRank = %d; %d wrong results for my_Gather" ANSI_COLOR_RESET "\n", myRank, num_of_wrong_results);
                    fflush(stdout);
                } else {
                    printf(ANSI_COLOR_GREEN   "my_Gather is OK"   ANSI_COLOR_RESET "\n");
                    fflush(stdout);
                }
            }
            break;
        case MY_SCATTER:
            if(myRank == 0) {
                printf("testing my_Scatter\n");
                fflush(stdout);
            }

            my_Scatter(big_buff, size_of_buff, MPI_INT, buff, size_of_buff, MPI_INT, root, MPI_COMM_WORLD);
            for(int i = 0; i < size_of_buff; i++){
                if(buff[i] != scatter_expected[i]){
                    num_of_wrong_results++;
                }
            }
            if(num_of_wrong_results != 0){
                printf(ANSI_COLOR_RED "myRank = %d; %d wrong results for my_Scatter" ANSI_COLOR_RESET "\n", myRank, num_of_wrong_results);
                fflush(stdout);
            } else {
                printf(ANSI_COLOR_GREEN   "myRank = %d, my_Scatter is OK"   ANSI_COLOR_RESET "\n", myRank);
                fflush(stdout);
            }
            break;
        case MY_REDUCE:
            if(myRank == 0) {
                printf("testing my_Reduce\n");
                fflush(stdout);
            }
            my_Reduce(buff, recvbuf, size_of_buff, MPI_INT, op_for_reduce, root, MPI_COMM_WORLD);
            if(myRank == 0) {
                for (int i = 0; i < size_of_buff; i++) {
                    if (recvbuf[i] != reduce_expected[i]) {
                        num_of_wrong_results++;
                    }
                }
                if (num_of_wrong_results != 0) {
                    printf(ANSI_COLOR_RED "wrong results for my_Reduce" ANSI_COLOR_RESET "\nMy resalts are: ");
                    fflush(stdout);
                    for(int j = 0; j < size_of_buff; j++){
                        printf("%d ", recvbuf[j]);
                    }
                    printf("\n");
                } else {
                    printf(ANSI_COLOR_GREEN   "my_Reduce is OK"   ANSI_COLOR_RESET "\n");
                    fflush(stdout);
                }
            }
            break;
        default:
            if(myRank == 0) {
                printf(ANSI_COLOR_RED "Now such option for test_my_functions" ANSI_COLOR_RESET "\n");
            }
    }


    free(buff);
    free(big_buff);
    free(recvbuf);
    free(gather_expected);
    free(scatter_expected);
    free(reduce_expected);
    free(bcast_expected);
    MPI_Barrier(MPI_COMM_WORLD);


    return 0;
}
