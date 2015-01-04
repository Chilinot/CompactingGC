#include <stdio.h>


#ifdef __sparc__
#define ICPU "sparc"
#endif

#ifdef __i386__
#define ICPU "x86"
#endif

#ifndef ICPU
#define ICPU "okänd"
#endif



#define printSize(type) printf("sizeof("#type") = %d\n", sizeof(type));

extern char ** environ;

struct struct1{
  char a;
  long long b; 
  char c;
};

struct struct2{
  double b; 
  char a;
  char c;
};


struct struct22{
  
  char a;
  char c;
  double b; 
};
struct struct222{
  short a , b, c;
char e;
};

struct struct3{
  char c;
  double b; 
  char a;
};

struct struct4{
  double b; 
  char a;
  char c;
  char d;
  char e;
};


struct struct5{
  char a;
  char c;
  char d;
  char e;
  char b; 
};


struct struct6{
  char a;
  void* b;
};



struct struct7{
  char a;  
  int c;
  
  char b;
};


struct struct8{
  int c;
  char d;
  char a;
  char b;
};


struct struct9{
  int c;
  char a;
  int e;

};

struct struct10{
  
  
  double d;
  int c;
  int e;  
  char a;
  

};



struct struct_fd{
float a;
  double d;
};


int main(){
  //printf("%d bitar\n", (sizeof(void*)*8));
  if(sizeof(void*) == 8){
    puts("64 bitar");
  }
  if(sizeof(void*) == 4){
    puts("32 bitar");
  }

  printf("cpu: %s\n", ICPU);
  /*
    for(int i=0; strlen(environ[i]) > i; i++){
      puts(environ[i]);
    }
  */
  printSize(char);
  printSize(double);
  printSize(int);
  printSize(float);
  printSize(void*)
  printSize(long);
  printSize(long long);
  printSize(short);
  printSize(struct struct1);
  printSize(struct struct2);
  printSize(struct struct3);
  printSize(struct struct4);
  printSize(struct struct5);
  printSize(struct struct6);
  printSize(struct struct7);
  printSize(struct struct22);
  printSize(struct struct8);
  printSize(struct struct9);
  printSize(struct struct10);
printSize(struct struct222);
printSize(struct struct_fd);

  struct struct4 minstruct = {3.14159265358979323, 'a','b','c','d'};

  printf("break here");
  return 0;
}
