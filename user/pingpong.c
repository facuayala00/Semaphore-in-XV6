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
	printf("%d el numero para chequear (despues sacar) \n", rally);

	//TESTEO DE SYSCALL
	int a = sem_open();
	a = a;

  // int pid_a = fork();
	// if (pid_a < 0) {
	// 	printf("erroraso del fork \n");
	// }
	// else if (pid_a == 0){
	// 	for(unsigned int i = 0; i < rally; i++){
	// 		printf("ping \n");
	// 	}
	// 	exit(0); //mato al beibi (que cruel que suena)
	// }

	// int pid_b = fork();
	// if (pid_b < 0) {
	// 	printf("erroraso del fork \n");
	// }
	// else if (pid_b == 0){
	// 	for(unsigned int i = 0; i < rally; i++){
	// 		printf("pong \n");
	// 	}
	// 	exit(0); //mato al beibi (que cruel que suena)
	// }

  exit(0);
}