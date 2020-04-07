//
// Created by ilya on 01.04.2020.
//

#include "lol.h"

int my_Bcast(void *buf, int count, MPI_Datatype type, int root, MPI_Comm comm) {
    int numOfProcs, myRank;
    MPI_Status status;
    MPI_Comm_size(comm, &numOfProcs);
    MPI_Comm_rank(comm, &myRank);
    if (myRank == root) {
        for (int i = 0; i < numOfProcs; i++) {
            if (i != root) {
                MPI_Send(buf, count, type, i, MY_BROADCAST, comm);
            }
        }
    } else {
        MPI_Recv(buf, count, type, root, MY_BROADCAST, comm, &status);
    }

    return 0;
}

int my_Scatter(void *sbuf, int scount, MPI_Datatype stype, void *rbuf, int rcount, MPI_Datatype rtype, int root,
               MPI_Comm comm) {
    int numOfProcs, myRank;
    MPI_Status status;
    MPI_Comm_size(comm, &numOfProcs);
    MPI_Comm_rank(comm, &myRank);

    if (myRank == root) {
        for (int i = 0; i < numOfProcs; i++) {
            if (i != root) {
                MPI_Send(sbuf, scount, stype, i, MY_SCATTER, comm);
            } else {
                MPI_Send(sbuf, scount, stype, i, MY_SCATTER, comm);
                MPI_Recv(rbuf, rcount, rtype, root, MY_SCATTER, comm, &status);
            }
            sbuf += scount;
        }
    } else {
        MPI_Recv(rbuf, rcount, rtype, root, MY_SCATTER, comm, &status);
    }

    return 0;
}

int my_Gather(void *sbuf, int scount, MPI_Datatype stype, void *rbuf, int rcount, MPI_Datatype rtype, int root,
              MPI_Comm comm) {
    int numOfProcs, myRank;
    MPI_Status status;
    MPI_Comm_size(comm, &numOfProcs);
    MPI_Comm_rank(comm, &myRank);

    if (myRank == root) {
        for (int i = 0; i < numOfProcs; i++) {
            if (i != root) {
                MPI_Recv(rbuf, rcount, rtype, i, MY_GATHER, comm, &status);
            } else { rbuf = sbuf; }
            rbuf += rcount;
        }
    } else {
        MPI_Send(sbuf, scount, stype, root, MY_GATHER, comm);
    }

    return 0;
}

int my_Reduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype type, MPI_Op op, int root,
              MPI_Comm comm) { //Only for int
    int numOfProcs, myRank;
    MPI_Status status;
    MPI_Comm_size(comm, &numOfProcs);
    MPI_Comm_rank(comm, &myRank);
    if (type != MPI_INT && myRank == root) {
        fprintf(stderr, "Incompatible type of data\n");
        exit(0);
    }
    if (myRank == root) {
        int **inter_buff = malloc(numOfProcs * sizeof(int *));

        for (int i = 0; i < numOfProcs; i++) {
            inter_buff[i] = malloc(count * sizeof(int));
            if (i != root) {
                MPI_Recv(inter_buff[i], count, type, i, MY_REDUCE, comm, &status);
            } else { inter_buff[i] = sendbuf; }
        }

        switch (op) {
            case MPI_MAX:
                find_MAX(inter_buff, numOfProcs, count, recvbuf);
                break;

            case MPI_MIN:
                find_MIN(inter_buff, numOfProcs, count, recvbuf);
                break;

            case MPI_SUM:
                find_SUM(inter_buff, numOfProcs, count, recvbuf);
                break;

            case MPI_PROD:
                find_PROD(inter_buff, numOfProcs, count, recvbuf);
                break;

            case MPI_LAND:
                find_LAND(inter_buff, numOfProcs, count, recvbuf);
                break;

            case MPI_BAND:
                find_BAND(inter_buff, numOfProcs, count, recvbuf);
                break;

            case MPI_LOR:
                find_LOR(inter_buff, numOfProcs, count, recvbuf);
                break;

            case MPI_BOR:
                find_BOR(inter_buff, numOfProcs, count, recvbuf);
                break;

            case MPI_LXOR:
                find_LXOR(inter_buff, numOfProcs, count, recvbuf);
                break;

            case MPI_BXOR:
                find_BXOR(inter_buff, numOfProcs, count, recvbuf);
                break;

            case MPI_MAXLOC:
                find_MAXLOC(inter_buff, numOfProcs, count, recvbuf);
                break;

            case MPI_MINLOC:
                find_MINLOC(inter_buff, numOfProcs, count, recvbuf);
                break;
            default:
                fprintf(stderr, "my_Reduce: No such command\n");
                break;
        }

        for (int i = 0; i < numOfProcs; i++) {
            free(inter_buff[i]);
        }

    } else {
        MPI_Send(sendbuf, count, type, root, MY_REDUCE, comm);
    }
    return 0;
}
