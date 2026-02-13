#include <stdio.h>
#include "main.h"
#include <string.h>

int main(){
int x = 1;
char input[5];
int  num;
while( x > 0){
int i = 0;
printf("Enter push, pop, or end ");
scanf("%s", input);

if (strcmp(input, "push") == 0){
  printf("%s\n","insert value to push");
  scanf("%d", &num);
  push(num);
  ++i;
      }
else if (strcmp(input, "pop") == 0){
   pop();
  ++i;
}
else if (strcmp(input, "end") ==0){
  printf("%s\n", "Displaying stack");
  end();
  x = x-x;
  ++i;
  break;
}
else if((strcmp(input, "push") != 0)||(strcmp(input, "pop")!= 0)||(strcmp(input,"end")!= 0)/*|| (i==0)*/) {
  printf("      ERROR: INVALID INPUT      ");
  break;
}
}
}