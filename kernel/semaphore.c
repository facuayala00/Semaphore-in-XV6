#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "proc.h"
#include "fs.h"
#include "sleeplock.h"
#include "file.h"

#define ERROR 0
#define SUCCESS 1
#define SEM_ARRAY_LENGTH 64

//Parte que iría en sysproc.c
uint64
sys_sem_open(void)
{
  int sem, value;
  argint(0, &sem);
  argint(1, &value);
  return sem_open(sem, value);
}

uint64
sys_sem_close(void)
{
  int sem;
  argint(0, &sem);
  return sem_close(sem);
}

uint64
sys_sem_up(void)
{
  int sem;
  argint(0, &sem);
  return sem_up(sem);
}

uint64
sys_sem_down(void)
{
  int sem;
  argint(0, &sem);
  return sem_down(sem);
}
//fin de parte de sysproc.c


//código que iría en proc.c

struct semaphore {
    struct spinlock lock;
    int max_value;
    int active;
    int value;
};


struct semaphore sem_array[64]; 
struct spinlock sem_lock;

int 
sem_open(int sem, int value)
{
  if (sem_array[sem].active == 1) {
    return ERROR;
  }else {
    acquire(&sem_lock);
    sem_array[sem].value = value;
    sem_array[sem].max_value = value;
    sem_array[sem].active = 1;
    release(&sem_lock);
    return SUCCESS;
  }


}

int 
sem_close(int sem)
{
  if (sem_array[sem].value != sem_array[sem].max_value) {
    return ERROR;
  }else {
    acquire(&sem_lock);
    sem_array[sem].value = 0;
    sem_array[sem].max_value = 0;
    sem_array[sem].active = 0;
    release(&sem_lock);
    return SUCCESS;
  }

}

int 
sem_up(int sem)
{
  if (sem_array[sem].value >= sem_array[sem].max_value) {
    return ERROR;
  }else {
  acquire(&sem_lock);
  sem_array[sem].value++;
  wakeup(&sem_array[sem]);
  release(&sem_lock);
  return SUCCESS;
  }

}

int 
sem_down(int sem)
{
  acquire(&sem_lock);

  if (sem_array[sem].value > 0) {
    sem_array[sem].value--;
  } 
  else { //caso (sem_array[sem] <= 0)
    printf("Sem en 0 \n");
  }
  if (sem_array[sem].value == 0) {
    sleep(&sem_array[sem], &sem_lock);
  }

  if (sem_array[sem].value < 0) {
    return ERROR;
  }else {
    release(&sem_lock);
    return SUCCESS;
  }
}