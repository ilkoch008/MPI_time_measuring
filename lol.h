//
// Created by ilya on 03.04.2020.
//

#ifndef MEASURING_TIME_LOL_H
#define MEASURING_TIME_LOL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "mpi.h"
#include <string.h>

#define MY_BROADCAST 11
#define MY_REDUCE 22
#define MY_GATHER 33
#define MY_SCATTER 44

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int run_MPI_fun(int length, int iterations, int *sendBuff, int *recvBuff, int *scatterSendBuff);

int run_my_fun(int length, int iterations, int *sendBuff, int *recvBuff, int *scatterSendBuff);

int my_Bcast(void *buf, int count, MPI_Datatype type, int root, MPI_Comm comm);

int my_Reduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype type, MPI_Op op, int root, MPI_Comm comm);

int my_Scatter(void *sbuf, int scount, MPI_Datatype stype, void *rbuf, int rcount, MPI_Datatype rtype, int root,
               MPI_Comm comm);

int my_Gather(void *sbuf, int scount, MPI_Datatype stype, void *rbuf, int rcount, MPI_Datatype rtype, int root,
              MPI_Comm comm);

int find_MAX(int size_of_buff, int index, const int *sendbuf, int *recvbuf);
int find_MIN(int size_of_buff, int index, const int *sendbuf, int *recvbuf);
int find_SUM(int size_of_buff, int index, const int *sendbuf, int *recvbuf);
int find_PROD(int size_of_buff, int index, const int *sendbuf, int *recvbuf);
int find_LAND(int size_of_buff, int index, const int *sendbuf, int *recvbuf);
int find_BAND(int size_of_buff, int index, const int *sendbuf, int *recvbuf);
int find_LOR(int size_of_buff, int index, const int *sendbuf, int *recvbuf);
int find_BOR(int size_of_buff, int index, const int *sendbuf, int *recvbuf);
int find_LXOR(int size_of_buff, int index, const int *sendbuf, int *recvbuf);
int find_BXOR(int size_of_buff, int index, const int *sendbuf, int *recvbuf);
int find_MAXLOC(int size_of_buff, int index, const int *sendbuf, int *recvbuf, int *previous_max);
int find_MINLOC(int size_of_buff, int index, const int *sendbuf, int *recvbuf, int *previous_min);

int test_my_functions(int func_for_testing);

int size_of(MPI_Datatype type);

MPI_Op define_func_for_reduce(char * str);

#endif //MEASURING_TIME_LOL_H
