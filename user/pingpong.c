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

  int err_open_a = sem_open(0, 1);    //semaforo del papi
  if (err_open_a == 0){
    printf("erroraso del sem_open\n");
    exit(1);
  }

  int err_open_b = sem_open(9, 1);  //semaforo del hijo
  if (err_open_b == 0){
    printf("erroraso del sem_open\n");
    exit(1);
  }

  int nash = sem_down(9);   //le restamos para "inicializarlo" en 0
  if(nash == 0){
    printf("erroraso del sem_down \n");
    exit(1);
  }


  int pid = fork();
  if (pid < 0) {
    printf("erroraso del fork \n");
    exit(1);
  }
  if (pid > 0) { //padre
    for (uint i = 0; i < rally; i++) {
      int err_down = sem_down(0);
      if (err_down == 0) {
        printf("Erroraso del down del padre \n");
        exit(1);
      }
      printf("ping \n"); 

      int err_up = sem_up(9);
      if (err_up == 0) {
        printf("Erroraso del up al hijo desde el padre \n");
        exit(1);
      }
    } 
  }

  else if (pid == 0) {
    for (uint i = 0; i < rally; i++) {
      int err_down = sem_down(9);
      if (err_down == 0) {
        printf("Erroraso del down del beibi \n");
        exit(1);
      }
      printf("          pong \n"); 

      int err_up = sem_up(0);
      if (err_up == 0) {
        printf("Erroraso del up al padre desde el hijitus \n");
        exit(1);
      }
    } 
    exit(0); //sacrifico al beibi a los dioses supremos del abismo
  }

  wait(0);

  int err_close_p = sem_close(0); //cierro al padre
  if (err_close_p == 0) {
    printf("error close padre \n");
    exit(1);
  }

  int err_up = sem_up(9);
  if (err_up == 0) {
    printf("Erroraso del up al padre desde el hijitus \n");
    exit(1);
  }
  int err_close_b = sem_close(9); //cierro al beibi
  if (err_close_b == 0) {
    printf("error close padre \n");
    exit(1);
  }


  exit(0);
}
