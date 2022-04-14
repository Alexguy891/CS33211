#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 2 // Max number of items and buffer

struct shm {
    sem_t emp;
    sem_t full;
    int buf[SIZE];
};