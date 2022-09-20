/*
saque este codigo de una pagina

*/


#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
////////////////
//Functions
//////
void printcow(void);
void displayhelp(void);
void displaycowlist(void);

////////////////
//Variables
//////
char eyes='o';
char upperbubble='\\';
char lowerbubble='\\';

unsigned int counter;
unsigned int argscharcount=0;
unsigned int nextarg;
unsigned short skiparg;
unsigned short thought=0;

int main(int argc, char *argv[]) {

    /*Handle Arguments*/
    if( argc == 1 ) {
        displayhelp();
        exit(1);
    }

    /* Count characters in non-flag arguments */
    for(counter=1; counter < argc; counter++) {
            argscharcount=(argscharcount + 1 + (strlen(argv[counter])));
    }
    if (argscharcount == 0) {
        displayhelp();
        exit(1);
    }
    argscharcount=argscharcount + 1;

    /* Display speech bubble */
    fprintf(2," ");
    for(counter=1; counter <= argscharcount; counter++) {
        fprintf(2,"_");
    }

    if ( thought == 0 ) {
        fprintf(2,"\n< ");
    }
    else if ( thought == 1 ) {
        fprintf(2,"\n( ");
    }

    for(counter=1; counter < argc; counter++) {
        printf("%s ", argv[counter]);
    }

    if ( thought == 0 ) {
        fprintf(2,">\n ");
    }
    else if ( thought == 1 ) {
        fprintf(2,")\n ");
    }
    for(counter=1; counter <= argscharcount; counter++) {
        fprintf(2,"-");
    }
    fprintf(2,"\n");
    printcow();
    return 0;
}

void displayhelp(void) {
    fprintf(2, "Mini cowsay clave, no se pueden pipear comandos y no se puede usar argumentos, toma todo como texto a printear");
}

void printcow(void) {
fprintf(2,"        %c   ^__^\n\
         %c  (%c%c)\\_______\n\
            (__)\\       )\\/\\\n\
                ||----w |\n\
                ||     ||\n", upperbubble, lowerbubble, eyes, eyes);
}