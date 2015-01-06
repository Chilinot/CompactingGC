#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <stdint.h>

#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__


#define ANALYS(a, ...) \
  
#define INC(x) PRIMITIVE_CAT(INC_, x)

#define STRUCT_MK_HELPER(a, ...) 
//#define STRUCT_MK_i(name, ...) 
//struct name { STRUCT_MK_(a)

// the offset form address a to b
// exemple
//  0 1 2 3 4 5
// <--a---b---->
// offset(b, a) => 3-1 => 2 
#define offset(a, b) ((uintptr_t)&b) - ((uintptr_t) &a)

#define drawins(canvas, a, b, c) memset(canvas + offset(a, b) , *#c , sizeof(b))
//sizeof(CAT(strukt, CAT( '.' , a))))

int main(int argc, char *argv[])
{
  struct structx {
    double a; 
    long b; 
    int c;
    void *d;
    char e;
};
  
  struct structx foobar;
  size_t foobarSize = (sizeof(foobar));
  char outputStr[foobarSize+1];
  memset(outputStr, '.', foobarSize); // satter alla tacken till '.'
  outputStr[foobarSize] = '\0'; // terminerings tecken
  //memset(outputStr+ offset(foobar, foobar.a) , 'a', sizeof(foobar.a));
  //drawins(outputStr, foobar , foobar.a, i);double
  drawins(outputStr, foobar , foobar.a, a);
  drawins(outputStr, foobar , foobar.b, b);
  drawins(outputStr, foobar , foobar.c, c);
  drawins(outputStr, foobar , foobar.d, d);
  drawins(outputStr, foobar , foobar.e, e);
  

  //printf("size = %x\n", offset(foobar, foobar.a));
  printf("size = %x\n", offset(foobar, foobar.b));
  printf("size = %x\n", offset(foobar, foobar.c));
  for(int i=0; i<sizeof(outputStr); i++){
    void inget(){}
    putchar(outputStr[i]);
    (i+1)%4 == 0 ? putchar(' ') : inget();
  }
  putchar('\n');
	 
  return 0;
}
