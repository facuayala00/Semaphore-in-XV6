#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "proc.h"
#include "fs.h"
#include "sleeplock.h"
#include "file.h"

#define ERROR 0     //definicion de error
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
    struct spinlock lock; //indica si esta bloqueado
    int max_value;        //valor original del semaforo
    int active;           // indica si esta activo o no
    int value;            //valor que va cambiando (no puede superar max_value)
};


struct semaphore sem_array[64]; 


//abre el semaforo "sem" con el valor original "value"
int 
sem_open(int sem, int value)
{
  initlock(&sem_array[sem].lock, "sem");    //se inicia el lock por buena practica
  acquire(&sem_array[sem].lock);
  if (sem_array[sem].active == 1) {         //si el semaforo esta abierto, da error
    release(&sem_array[sem].lock);
    return ERROR;
  }else {
    sem_array[sem].value = value;
    sem_array[sem].max_value = value;
    sem_array[sem].active = 1;               //el semaforo pasa a estar activo
    release(&sem_array[sem].lock);
    return SUCCESS;
  }


}

//cierra el semaforo "sem"
int 
sem_close(int sem)
{
  acquire(&sem_array[sem].lock);
  if (sem_array[sem].value != sem_array[sem].max_value) {     // si value no es el valor original, da error
    release(&sem_array[sem].lock);
    return ERROR;
  }else {

    sem_array[sem].value = 0;         //por convención ponemos 0
    sem_array[sem].max_value = 0;
    sem_array[sem].active = 0;        //el semaforo pasa a estar inactivo
    release(&sem_array[sem].lock);
    return SUCCESS;
  }

}

//incrementa el semaforo "sem"
int 
sem_up(int sem)
{
  acquire(&sem_array[sem].lock);
  if (sem_array[sem].value >= sem_array[sem].max_value) { //si se supera el valor original, da error
    release(&sem_array[sem].lock);
    return ERROR;
  }else {

  sem_array[sem].value++;
  wakeup(&sem_array[sem]);        //si un semaforo esta dormido, wakeup() lo despierta
  release(&sem_array[sem].lock);
  return SUCCESS;
  }

}

//decrementa el semaforo "sem"
int 
sem_down(int sem)
{
  acquire(&sem_array[sem].lock);
  if (sem_array[sem].active < 0) { //el arreglo esta inactivo
    release(&sem_array[sem].lock);
    return ERROR;
  } 
  else {                           // se decrementa normal
    if (sem_array[sem].value > 0) {
      sem_array[sem].value--;
    } 
    else { //si (sem_array[sem].value == 0)
      while (sem_array[sem].value == 0) {
        sleep(&sem_array[sem], &sem_array[sem].lock);  //se intento pedir recurso en 0 por lo que se duerme el proceso
      }
      sem_array[sem].value--;         //apenas se despierta se "consume el recurso"
    }
    release(&sem_array[sem].lock);
    return SUCCESS;
  }
}