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
	fprintf(2,"%d \n", rally);

  int pid_a = fork();
	if (pid_a < 0) {
		fprintf(2, "erroraso del fork \n");
	}
	else if (pid_a == 0){
		for(unsigned int i = 0; i < rally; i++){
			fprintf(2, "ping \n");
		}
	}

	int pid_b = fork();
	if (pid_b < 0) {
		fprintf(2, "erroraso del fork \n");
	}
	else if (pid_b == 0){
		for(unsigned int i = 0; i < rally; i++){
			fprintf(2, "pong \n");
		}
	}



  exit(0);
}