#include <stdio.h>
#include <string.h>
#include "exam.h"
int amt = 0;
int main(){
for (int i = 0; i < five; ++i){
  printf(" Word here");
  scanf("%s", word[i]);
  ++amt;
  if(amt > five){
    printf("Invalid input, you may only use 5 words and done.");
    break;
  }
  if (strlen(word[i]) > eleven){
    printf("Too many characters. Only 11 permitted per word");
  }
  if(strcmp(word[i], "DONE") == 0){
    break;
  }
  }
for (int i = 0; i < five; ++i){
  if(strcmp(word[i], "DONE") == 0){
    break;
  }
  printf("%s\n", word[i]);
}
printf("The alphabetically first word is: ");
first();
printf("The largest amount of characters: ");
leng();
}