#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int i = 1;
struct Node{
  int value;
  int address;
  struct Node *next;
};

struct Node *head = NULL;       //initialize head
                                //struct Node *cur = NULL;      //initialize cur

void push(int value){
  struct Node *n = (struct Node*)malloc(sizeof(struct Node));

  n->value = value;

  n->next = head;               //point to previous node

  head = n;
}

void pop(){
    struct Node *x = head;      //save first node
    if (head == NULL){
      printf("\n", "ERROR: STACK EMPTY ");
      return;
    }
    else{
    head = head -> next;                //sets head to next value
    printf("%s\n", "Popped value:");
    printf("%d\n", x->value,"\n");
    free(x);  //figure out what to free
    return;
    }
}
void end(){
  struct Node *cur = head;
  struct Node *prev = NULL;
  printf(" {\n");
  while(cur != NULL) {
    printf("(%d\n ", cur->value,"\n");
    cur = cur-> next;
  }
  printf(" } ");
}