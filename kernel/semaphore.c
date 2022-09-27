#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "proc.h"
#include "fs.h"
#include "sleeplock.h"
#include "file.h"


int sem_array[64]; 
int cont = 0;

int 
sem_open(int sem)
{
    printf("open magico %d \n", sem);
    return sem;
}

int 
sem_close(int sem)
{
    printf("close extravagente %d \n", sem);
    return sem;
}

int 
sem_up(int sem)
{
    printf("up epico %d \n", sem);
    return sem;
}

int 
sem_down(int sem)
{
    printf("down locura %d \n", sem);
    return sem;
}