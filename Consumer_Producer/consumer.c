#include "producer-consumer.h"

int main() {
    int sh = shm_open("/sharedVal", O_RDWR, 0);
    if(sh == -1)
        errExit("shmp_open");
    
    struct shm *s = mmap(NULL, sizeof(*s), PROT_READ | PROT_WRITE, MAP_SHARED, sh, 0);
    
    if(s == MAP_FAILED)
        errExit("mmap");

}