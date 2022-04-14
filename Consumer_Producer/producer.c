#include "producer-consumer.h"
#include <sys/mman.h>
#include <ctype.h>

int main() {
    int sh = shm_open("/sharedVal", O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
    if(sh == -1)
        errExit("shm_open");
    
    if(ftruncate(sh, sizeof(struct shm)) == -1)
        errExit("ftruncate");

    struct shm *s = mmap(NULL, sizeof(*s), PROT_READ | PROT_WRITE, MAP_SHARED, sh, 0);

    if(s == MAP_FAILED)
        errExit("mmap");
    
    if(sem_init(&s->emp, 1, 0) == -1)
        errExit("sem_init-sem1");
    if(sem_init(&s->full, 1, 0) == -1)
        errExit("sem_init-sem2");
    
    if(sem_wait(&s->emp) == -1)
        errExit("sem_wait");
    
    if(sem_post(&s->full) == -1)
        errExit("sem_post");

    exit(EXIT_SUCCESS);
}