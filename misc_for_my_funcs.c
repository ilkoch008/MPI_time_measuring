//
// Created by ilya on 07.04.2020.
//

#include "lol.h"

int find_MAX(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf) {
    for (int i = 0; i < size_of_buff; i++) {
        recvbuf[i] = (-__INT_MAX__ - 1);
        for (int j = 0; j < num_of_buffs; j++) {
            if (buffs[j][i] > recvbuf[i]) {
                recvbuf[i] = buffs[j][i];
            }
        }
    }
}

int find_MIN(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf) {
    for (int i = 0; i < size_of_buff; i++) {
        recvbuf[i] = __INT_MAX__;
        for (int j = 0; j < num_of_buffs; j++) {
            if (buffs[j][i] < recvbuf[i]) {
                recvbuf[i] = buffs[j][i];
            }
        }
    }
}

int find_SUM(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf) {
    for (int i = 0; i < size_of_buff; i++) {
        recvbuf[i] = 0;
        for (int j = 0; j < num_of_buffs; j++) {
            recvbuf[i] += buffs[j][i];
        }
    }
}

int find_PROD(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf) {
    for (int i = 0; i < size_of_buff; i++) {
        recvbuf[i] = 1;
        for (int j = 0; j < num_of_buffs; j++) {
            recvbuf[i] *= buffs[j][i];
        }
    }
}

int find_LAND(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf) {
    for (int i = 0; i < size_of_buff; i++) {
        recvbuf[i] = buffs[0][i];
        for (int j = 0; j < num_of_buffs; j++) {
            recvbuf[i] = (buffs[j][i] && recvbuf[i]);
        }
    }
}

int find_BAND(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf) {
    for (int i = 0; i < size_of_buff; i++) {
        recvbuf[i] = __INT_MAX__;
        for (int j = 0; j < num_of_buffs; j++) {
            recvbuf[i] &= buffs[j][i];
        }
    }
}

int find_LOR(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf) {
    for (int i = 0; i < size_of_buff; i++) {
        recvbuf[i] = buffs[0][i];
        for (int j = 0; j < num_of_buffs; j++) {
            recvbuf[i] = (buffs[j][i] || recvbuf[i]);
        }
    }
}

int find_BOR(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf) {
    for (int i = 0; i < size_of_buff; i++) {
        recvbuf[i] = 0;
        for (int j = 0; j < num_of_buffs; j++) {
            recvbuf[i] |= buffs[j][i];
        }
    }
}

int find_LXOR(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf) {
    for (int i = 0; i < size_of_buff; i++) {
        recvbuf[i] = buffs[0][i];
        for (int j = 0; j < num_of_buffs; j++) {
            recvbuf[i] = (buffs[j][i] != recvbuf[i]);
        }
    }
}

int find_BXOR(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf) {
    for (int i = 0; i < size_of_buff; i++) {
        recvbuf[i] = buffs[0][i];
        for (int j = 0; j < num_of_buffs; j++) {
            recvbuf[i] ^= buffs[j][i];
        }
    }
}

int find_MAXLOC(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf) {
    for (int i = 0; i < size_of_buff; i++) {
        recvbuf[i] = (-__INT_MAX__ - 1);
        for (int j = 0; j < num_of_buffs; j++) {
            if (buffs[j][i] > recvbuf[i]) {
                recvbuf[i] = j;
            }
        }
    }
}

int find_MINLOC(int **buffs, int num_of_buffs, int size_of_buff, int *recvbuf) {
    for (int i = 0; i < size_of_buff; i++) {
        recvbuf[i] = __INT_MAX__;
        for (int j = 0; j < num_of_buffs; j++) {
            if (buffs[j][i] < recvbuf[i]) {
                recvbuf[i] = j;
            }
        }
    }
}
