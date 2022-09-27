#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "proc.h"
#include "fs.h"
#include "sleeplock.h"
#include "file.h"

int cant_proc = 0;
int sem_array[64];



int sem_open(int sem, int value);

int sem_close(int sem);

int sem_up(int sem);

int sem_down(int sem);