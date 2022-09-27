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
sem_open(int sem, int value)
{
    if (sem_array[sem] != 0) { //esta guarda esta mal?
        printf("hermano ya se reservó ese sem \n");
        return 0;
    }
    sem_array[sem] = value;
    printf("aca tenes tu super semaforo :3 \n");
    return 1;
}

int 
sem_close(int sem)
{
    sem_array[sem] = 0;
    return 1;
}

int 
sem_up(int sem)
{
    sem_array[sem]++;
    return 1;
}

int 
sem_down(int sem)
{
    if (sem_array[sem] == 0) {
        printf("flaco ya estamos en 0 no bajes mas \n");
        return 0;
    }
    else {
        sem_array[sem]--;
        if (sem_array[sem] == 0) {
            printf("a noniiiiiiir USAR LOCKS Y WAASDJLASDJASJ\n");
        }
    }
    return 1;
}