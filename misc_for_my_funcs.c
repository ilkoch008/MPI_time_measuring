//
// Created by ilya on 07.04.2020.
//

#include "lol.h"

int find_MAX(int size_of_buff, int index, const int *sendbuf, int *recvbuf) {
    if (index == 0) {
        for (int j = 0; j < size_of_buff; j++) {
            recvbuf[index] = -__INT_MAX__;
        }
    }
    for (int j = 0; j < size_of_buff; j++) {
        if (sendbuf[j] > recvbuf[j]) {
            recvbuf[j] = sendbuf[j];
        }
    }
    return 0;
}

int find_MIN(int size_of_buff, int index, const int *sendbuf, int *recvbuf) {
    if (index == 0) {
        for (int j = 0; j < size_of_buff; j++) {
            recvbuf[j] = __INT_MAX__;
        }
    }
    for (int j = 0; j < size_of_buff; j++) {
        if (sendbuf[j] < recvbuf[j]) {
            recvbuf[j] = sendbuf[j];
        }
    }
    return 0;
}

int find_SUM(int size_of_buff, int index, const int *sendbuf, int *recvbuf) {
    if (index == 0) {
        for (int j = 0; j < size_of_buff; j++) {
            recvbuf[j] = 0;
        }
    }
    for (int j = 0; j < size_of_buff; j++) {
        recvbuf[j] += sendbuf[j];
    }
    return 0;
}

int find_PROD(int size_of_buff, int index, const int *sendbuf, int *recvbuf) {
    if (index == 0) {
        for (int j = 0; j < size_of_buff; j++) {
            recvbuf[j] = 1;
        }
    }
    for (int j = 0; j < size_of_buff; j++) {
        recvbuf[j] *= sendbuf[j];
    }
    return 0;
}

int find_LAND(int size_of_buff, int index, const int *sendbuf, int *recvbuf) {
    if (index == 0) {
        for (int j = 0; j < size_of_buff; j++) {
            recvbuf[j] = sendbuf[j];
        }
    }
    for (int j = 0; j < size_of_buff; j++) {
        recvbuf[j] = (sendbuf[j] && recvbuf[j]);
    }
    return 0;
}

int find_BAND(int size_of_buff, int index, const int *sendbuf, int *recvbuf) {
    if (index == 0) {
        for (int j = 0; j < size_of_buff; j++) {
            recvbuf[j] = sendbuf[j];
        }
    }
    for (int j = 0; j < size_of_buff; j++) {
        recvbuf[j] &= sendbuf[j];
    }
    return 0;
}

int find_LOR(int size_of_buff, int index, const int *sendbuf, int *recvbuf) {
    if (index == 0) {
        for (int j = 0; j < size_of_buff; j++) {
            recvbuf[j] = sendbuf[j];
        }
    }
    for (int j = 0; j < size_of_buff; j++) {
        recvbuf[j] = (sendbuf[j] || recvbuf[j]);
    }
    return 0;
}

int find_BOR(int size_of_buff, int index, const int *sendbuf, int *recvbuf) {
    if (index == 0) {
        for (int j = 0; j < size_of_buff; j++) {
            recvbuf[j] = sendbuf[j];
        }
    }
    for (int j = 0; j < size_of_buff; j++) {
        recvbuf[j] |= sendbuf[j];
    }
    return 0;
}

int find_LXOR(int size_of_buff, int index, const int *sendbuf, int *recvbuf) {
    if (index == 0) {
        for (int j = 0; j < size_of_buff; j++) {
            recvbuf[j] = sendbuf[j];
        }
    }
    for (int j = 0; j < size_of_buff; j++) {
        recvbuf[j] = (sendbuf[j] != recvbuf[j]);
    }
    return 0;
}

int find_BXOR(int size_of_buff, int index, const int *sendbuf, int *recvbuf) {
    if (index == 0) {
        for (int j = 0; j < size_of_buff; j++) {
            recvbuf[j] = sendbuf[j];
        }
    }
    for (int j = 0; j < size_of_buff; j++) {
        recvbuf[j] ^= sendbuf[j];
    }
    return 0;
}

int find_MAXLOC(int size_of_buff, int index, const int *sendbuf, int *recvbuf, int *previous_max) {
    if (index == 0) {
        for (int j = 0; j < size_of_buff; j++) {
//            printf("%d ", sendbuf[j]);
            recvbuf[j] = sendbuf[j];
            previous_max[j] = -__INT_MAX__;
        }
//        printf("\n");
    }
    for (int j = 0; j < size_of_buff; j++) {
        if (sendbuf[j] > previous_max[j]) {
            previous_max[j] = sendbuf[j];
            recvbuf[j] = index;
        }
    }
    return 0;
}

int find_MINLOC(int size_of_buff, int index, const int *sendbuf, int *recvbuf, int *previous_min) {
    if (index == 0) {
        for (int j = 0; j < size_of_buff; j++) {
            recvbuf[j] = sendbuf[j];
            previous_min[j] = __INT_MAX__;
        }
    }
    for (int j = 0; j < size_of_buff; j++) {
        if (sendbuf[j] < previous_min[j]) {
            previous_min[j] = sendbuf[j];
            recvbuf[j] = index;
        }
    }
    return 0;
}

int size_of(MPI_Datatype type) {
    switch (type) {
        case MPI_CHAR:
            return sizeof(char);

        case MPI_SIGNED_CHAR:
            return sizeof(signed char);

        case MPI_UNSIGNED_CHAR:
            return sizeof(unsigned char);

        case MPI_BYTE:
            return 1;

        case MPI_WCHAR:
            return sizeof(wchar_t);

        case MPI_SHORT:
            return sizeof(short);

        case MPI_UNSIGNED_SHORT:
            return sizeof(unsigned short);

        case MPI_INT:
            return sizeof(int);

        case MPI_UNSIGNED:
            return sizeof(unsigned);

        case MPI_LONG:
            return sizeof(long);

        case MPI_UNSIGNED_LONG:
            return sizeof(unsigned long);

        case MPI_FLOAT:
            return sizeof(float);

        case MPI_DOUBLE:
            return sizeof(double);

        case MPI_LONG_DOUBLE:
            return sizeof(long double);

        case MPI_LONG_LONG_INT:
            return sizeof(long long int);

        case MPI_UNSIGNED_LONG_LONG:
            return sizeof(unsigned long long);
        default:
            return 0;
    }
}

MPI_Op define_func_for_reduce(char * str){
    if(strstr(str, "MPI_MAXLOC") != NULL){
        return MPI_MAXLOC;
    }
    if(strstr(str, "MPI_MINLOC") != NULL){
        return MPI_MINLOC;
    }
    if(strstr(str, "MPI_SUM") != NULL){
        return MPI_SUM;
    }
    if(strstr(str, "MPI_MAX") != NULL){
        return MPI_MAX;
    }
    if(strstr(str, "MPI_MIN") != NULL){
        return MPI_MIN;
    }
    if(strstr(str, "MPI_PROD") != NULL){
        return MPI_PROD;
    }
    if(strstr(str, "MPI_LAND") != NULL){
        return MPI_LAND;
    }
    if(strstr(str, "MPI_BAND") != NULL){
        return MPI_BAND;
    }
    if(strstr(str, "MPI_LOR") != NULL){
        return MPI_LOR;
    }
    if(strstr(str, "MPI_BOR") != NULL){
        return MPI_BOR;
    }
    if(strstr(str, "MPI_LXOR") != NULL){
        return MPI_LXOR;
    }
    if(strstr(str, "MPI_BXOR") != NULL){
        return MPI_BXOR;
    }

    int myRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    if(myRank == 0){
        printf(ANSI_COLOR_RED "Function for my_Reduce not found" ANSI_COLOR_RESET "\n");
    }
    return 0;

}
