#include <stdio.h>
#include <stdlib.h>

#include <setjmp.h>
#define Dump_registers()  \
  jmp_buf env;		  \
  if (setjmp(env)) abort();  \




int main(int argc, char* argv[]){
  extern char** environ;
  int i = 0;
  while(environ[i][0] != NULL)
    printf("hej %s \n" ,environ[i++] );
}
