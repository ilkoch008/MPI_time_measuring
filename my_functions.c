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
    MPI_Request request;
    MPI_Comm_size(comm, &numOfProcs);
    MPI_Comm_rank(comm, &myRank);
    if (myRank == root) {
        for (int i = 0; i < numOfProcs; i++) {
//            printf("sbuf: ");
//            for(int j = 0; j < scount; j++){
//                printf("%d ", *(int*)(sbuf + j*size_of(stype)));
//            }
//            printf("\n");
            if (i != root) {
                MPI_Send(sbuf, scount, stype, i, MY_SCATTER, comm);
            } else {
                MPI_Isend(sbuf, scount, stype, root, MY_SCATTER, comm, &request);
                MPI_Recv(rbuf, rcount, rtype, root, MY_SCATTER, comm, &status);
            }
            sbuf += scount * size_of(stype);
//            sleep(1);
        }
    } else {
        MPI_Recv(rbuf, rcount, rtype, root, MY_SCATTER, comm, &status);
//        printf("myRank = %d; rbuf: ", myRank);
//        for(int j = 0; j < scount; j++){
//            printf("%d ", *(int*)(rbuf + j*size_of(stype)));
//        }
//        printf("\n");

    }
    return 0;
}

int my_Gather(void *sbuf, int scount, MPI_Datatype stype, void *rbuf, int rcount, MPI_Datatype rtype, int root,
              MPI_Comm comm) {
    int numOfProcs, myRank;
    MPI_Status status;
    MPI_Request request;
    MPI_Comm_size(comm, &numOfProcs);
    MPI_Comm_rank(comm, &myRank);

    if (myRank == root) {
        for (int i = 0; i < numOfProcs; i++) {
            if (i != root) {
                MPI_Recv(rbuf, rcount, rtype, i, MY_GATHER, comm, &status);
            } else {
                MPI_Isend(sbuf, scount, stype, root, MY_GATHER, comm, &request);
                MPI_Recv(rbuf, rcount, rtype, root, MY_GATHER, comm, &status);
            }
            rbuf += rcount * size_of(rtype);
        }
    } else {
        MPI_Send(sbuf, scount, stype, root, MY_GATHER, comm);
    }

    return 0;
}

int my_Reduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype type, MPI_Op op, int root,
              MPI_Comm comm) { //Only for int
    int numOfProcs, myRank;
    int * previous = malloc(count * size_of(type));
    MPI_Status status;
    MPI_Comm_size(comm, &numOfProcs);
    MPI_Comm_rank(comm, &myRank);
    if (type != MPI_INT && myRank == root) {
        fprintf(stderr, "Incompatible type of data\n");
        exit(0);
    }
    if (myRank == root) {
        for (int i = 0; i < numOfProcs; i++) {
            if (i != root) {
                MPI_Recv(sendbuf, count, type, i, MY_REDUCE, comm, &status);
            }
//            for(int j = 0; j < count; j++){
//                printf("%d ", *(int*)(sendbuf+j*size_of(type)));
//            }
//            printf("\n");
            switch (op) {
                case MPI_MAX:
                    find_MAX(count, i, sendbuf, recvbuf);
                    break;

                case MPI_MIN:
                    find_MIN(count, i, sendbuf, recvbuf);
                    break;

                case MPI_SUM:
                    find_SUM(count, i, sendbuf, recvbuf);
                    break;

                case MPI_PROD:
                    find_PROD(count, i, sendbuf, recvbuf);
                    break;

                case MPI_LAND:
                    find_LAND(count, i, sendbuf, recvbuf);
                    break;

                case MPI_BAND:
                    find_BAND(count, i, sendbuf, recvbuf);
                    break;

                case MPI_LOR:
                    find_LOR(count, i, sendbuf, recvbuf);
                    break;

                case MPI_BOR:
                    find_BOR(count, i, sendbuf, recvbuf);
                    break;

                case MPI_LXOR:
                    find_LXOR(count, i, sendbuf, recvbuf);
                    break;

                case MPI_BXOR:
                    find_BXOR(count, i, sendbuf, recvbuf);
                    break;

                case MPI_MAXLOC:
                    find_MAXLOC(count, i, sendbuf, recvbuf, previous);
                    break;

                case MPI_MINLOC:
                    find_MINLOC(count, i, sendbuf, recvbuf, previous);
                    break;
                default:
                    fprintf(stderr, "my_Reduce: No such command\n");
                    break;
            }
        }
    } else {
        MPI_Send(sendbuf, count, type, root, MY_REDUCE, comm);
    }
    free(previous);
    return 0;
}
