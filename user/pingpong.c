#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


/* 
esqueleto super esqueletico del pingpong.c
El programa pingpong deberá hacer fork y con los dos procesos resultantes:
*/

void
main(int argc, char *argv[])
{
  int rally = atoi(argv[1]);
  if (rally == 0) {
    printf("minimo 1 porfi \n");
    exit(1);
  }

  int err = sem_open(0, 1);
  if (err == 0){
    printf("erroraso del sem_open\n");
    exit(1);
  }

  int pid_a = fork();
  if (pid_a < 0) {
    printf("erroraso del fork \n");
    exit(1);
  }
  else if (pid_a == 0){
    for(unsigned int i = 0; i < rally; i++){
      int a = sem_down(0);
      if (a == 0){
        printf("erroraso del sem_down \n");
        exit(1);
      }
      printf("ping \n");

      int b = sem_up(0);
      if(b == 0){
        printf("erroraso del sem_up \n");
        exit(1);
      }
    }
    exit(0); //mato al beibi (que cruel que suena)
  }

  int pid_b = fork();
  if (pid_b < 0) {
    printf("erroraso del fork \n");
  }
  else if (pid_b == 0){
    for(unsigned int i = 0; i < rally; i++){
      int a = sem_down(0);
      if (a == 0){
        printf("erroraso del sem_down \n");
        exit(1);
      }      

      printf("pong \n");

      int b = sem_up(0);
      if(b == 0){
        printf("erroraso del sem_up \n");
        exit(1);
      }     
    }
    exit(0); //mato al beibi (que cruel que suena)
  }

  if (pid_a >0 || pid_b>0) {
    wait(0);
  }
  wait(0);  //wait para que no se bugee el $ del shell

  err = sem_close(0);
  if(err == 0){
    printf("erroraso del close\n");
    exit(1);
  }

  exit(0);
}