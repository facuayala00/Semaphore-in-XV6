#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "proc.h"
#include "fs.h"
#include "sleeplock.h"
#include "file.h"
#include <alloca.h>
#include <stdlib.h>

int sem_array[64]; 
int cont = 0;

int sem_open(int sem){
    // sem = calloc(value, sizeof(int)); //Inicializamos sem con value elementos?
    // return sem;
    printf("hola \n");
}

int sem_close(int sem);

int sem_up(int sem);

int sem_down(int sem);