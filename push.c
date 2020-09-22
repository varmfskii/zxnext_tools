#include <stdlib.h>
#include "heap.h"

void push(node **heap, void *d, int (*cmp)(const void *,const void *)) {
  node *head;
  void *t;

  if (*heap==NULL) {
    head=(node *)malloc(sizeof(node));
    head->l=head->r=NULL;
    head->bal=1;
    head->d=d;
  } else {
    head=*heap;
    if (cmp(head->d, d)<0) {
      t=d;
      d=head->d;
      head->d=t;
    }
    if (head->bal) {
      push(&(head->l), d, cmp);
      head->bal=0;
    } else {
      push(&(head->r), d, cmp);
      head->bal=1;
    }
  }
  *heap=head;
}

