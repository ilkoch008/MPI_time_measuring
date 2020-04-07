//
// Created by ilya on 03.04.2020.
//

#ifndef MEASURING_TIME_LOL_H
#define MEASURING_TIME_LOL_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "mpi.h"

#define MY_BROADCAST 11
#define MY_REDUCE 22
#define MY_GATHER 33
#define MY_SCATTER 44

int run_MPI_fun(int length, int iterations, int *sendBuff, int *recvBuff, int *scatterSendBuff);

int run_my_fun(int length, int iterations, int *sendBuff, int *recvBuff, int *scatterSendBuff);

int my_Bcast(void *buf, int count, MPI_Datatype type, int root, MPI_Comm comm);

int my_Reduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype type, MPI_Op op, int root, MPI_Comm comm);

int my_Scatter(void *sbuf, int scount, MPI_Datatype stype, void *rbuf, int rcount, MPI_Datatype rtype, int root,
               MPI_Comm comm);

int my_Gather(void *sbuf, int scount, MPI_Datatype stype, void *rbuf, int rcount, MPI_Datatype rtype, int root,
              MPI_Comm comm);

int find_MAX(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf);

int find_MIN(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf);

int find_SUM(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf);

int find_PROD(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf);

int find_LAND(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf);

int find_BAND(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf);

int find_LOR(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf);

int find_BOR(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf);

int find_LXOR(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf);

int find_BXOR(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf);

int find_MAXLOC(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf);

int find_MINLOC(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf);

#endif //MEASURING_TIME_LOL_H
