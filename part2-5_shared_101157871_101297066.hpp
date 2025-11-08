#ifndef PART2_5_SHARED
#define PART2_5_SHARED

struct shared_vars {
    int multiple;
    int shared_counter;
};

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

//struct sembuf {
//    short sem_num;
//    short sem_op;
//    short sem_flg;
//};

#endif