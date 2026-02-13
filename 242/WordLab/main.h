#include <stdio.h>
#include <string.h>

const int five = 5;
const int eleven = 11;
char word[5][11];
int val = 0;
int cur = 0;
int max = 0;
int leng(){
  for(int i =0; i < five; ++i){
    cur = strlen(word[i]);
    //printf("%d\n", cur);
    if(cur > max){
      max = cur;
    }
  }
val = max;
printf ("%d\n", max);  
return val;
}
void first(){
  char alph[eleven];
  strncpy(alph,word[0],eleven);
  for(int i = 0; i < five; ++i){
    if((strcmp(alph,word[i]) > 0) && (strcmp(word[i], "DONE") != 0)){
      strncpy(alph,word[i],eleven);
    }
  //printf("%s\n", alph);
  }
    printf("%s\n", alph);
  
}