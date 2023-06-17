#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "defines.h"

sem_t *producer_sem;
sem_t *consumer_sem;

int main() {
    shm_unlink(SHARED_MEM_NAME);
    close_semaphores(consumer_sem, producer_sem);

    int shared_memory = shm_open(SHARED_MEM_NAME, O_RDWR | O_CREAT | O_EXCL, 0666);
    int file = ftruncate(shared_memory, PAYLOAD_OFFSET);
    void *mem_map;

    open_semaphores(&consumer_sem, &producer_sem);
    create_mmap(shared_memory, file, &mem_map);

    payload_t *payload = mem_map;

    int i = 1;
    int cnt = 0;
    while (cnt < MAX_CNT) {
        sem_wait(producer_sem);
        printf("Result received from consumer: %d\n\n", payload->result);
        printf("Putting in %d to work on now\n", i);
        payload->work = i;
        i++;
        struct timespec sleep_duration = (struct timespec) {.tv_sec = 0, .tv_nsec = 100000000};
        nanosleep(&sleep_duration, NULL);
        sem_post(consumer_sem);
        cnt++;
    }

    int nunmap_value = munmap(mem_map, PAYLOAD_OFFSET);
    if (nunmap_value == -1) {
        perror("Failure while unmapping memory");
    }

    close_semaphores(consumer_sem, producer_sem);
    shm_unlink(SHARED_MEM_NAME);
}
