#ifndef   DEFINES_H
#define   DEFINES_H

#include <semaphore.h>

#define ERROR           (-1)
#define SYNC_OFFSET     sizeof(sync_t)
#define PAYLOAD_OFFSET  sizeof(payload_t)
#define BUFFER_SIZE     (SYNC_OFFSET + PAYLOAD_OFFSET)
#define SHARED_MEM_NAME "/SharedMemObject"
#define SHARED_CON_SEM  "/SharedConsumerSemaphore"
#define SHARED_PROD_SEM "/SharedProducerSemaphore"
#define MAX_CNT         100

typedef struct sync {
    sem_t new_work;
    sem_t new_result;
    void *payload_offset;
} sync_t;

typedef struct payload {
    int work;
    int result;
} payload_t;

void create_mmap(int shared_memory, int file, void **mm_mp);
void open_semaphores(sem_t **con, sem_t **prod);
void close_semaphores(sem_t *con, sem_t *prod);

#endif // DEFINES_H
