#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include "defines.h"

void open_semaphores(sem_t **con, sem_t **prod) {
    *con = sem_open(SHARED_CON_SEM, O_CREAT, 0666, 0);
    *prod = sem_open(SHARED_PROD_SEM, O_CREAT, 0666, 0);

    if (*con == SEM_FAILED) {
        perror("Failure encountered while opening consumer semaphore");
        exit(ERROR);
    }
    if (*prod == SEM_FAILED) {
        perror("Failure encountered while opening producer semaphore");
        exit(ERROR);
    }
    printf("Successfully opened both semaphores!\n");
}

void close_semaphores(sem_t *con, sem_t *prod) {
    sem_close(con);
    sem_close(prod);
    sem_unlink(SHARED_CON_SEM);
    sem_unlink(SHARED_PROD_SEM);
}

void create_mmap(int shared_memory, int file, void **mm_mp) {
    if (shared_memory == -1) {
        perror("Failure while opening shared memobject");
        exit(ERROR);
    }
    if (file == -1) {
        perror("Failure while truncating file");
    }
    void *mem_map = mmap(NULL,
                         PAYLOAD_OFFSET,
                         PROT_READ | PROT_WRITE,
                         MAP_SHARED,
                         shared_memory, 0);

    if (mem_map == MAP_FAILED) {
        perror("Failure while mapping memory");
        exit(ERROR);
    }

    *mm_mp = mem_map;

    printf("Successfully created memory map!\n");
}
