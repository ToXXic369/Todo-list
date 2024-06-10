#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 255

int count=1;

typedef struct node {
  char objective[MAX];
  int num;
  int status;
  struct node *next;
}node;

void new_task(node **list);
void print_all(node *list);
void releasing(node *list);
void remove_task(node **list);
void update_status(node *list);

int main() {

  node *head=NULL;
  int operation;

  printf("[1] To add your tasks.\n");
  printf("[2] To display all your tasks.\n");
  printf("[3] To remove a tasks.\n");
  printf("[4] To mark a task completed.\n");
  printf("[5] To exit.\n");
 
  while (1) {
    do {
      printf("\nnumber>> ");
      scanf("%d",&operation);
      getchar();

      if (operation > count || operation < 0) {
        printf("please enter a valid task number\n");
      }
    }

    switch (operation) {
      case 1:
        new_task(&head);
        break;
      case 2:
        print_all(head);
        break;
      case 3:
        remove_task(&head);
        break;
      case 4:
        update_status(head);
        break;
      case 5:
        releasing(head);
        exit(0);
      default:
        printf("[%d] that's not a valid input\n",operation);
    }

  }
  return 0;
}

void new_task(node **list) {
  node *new=(node *)malloc(sizeof(node));
  if (new == NULL) {
    printf("ERROR ALLOCATING MEMORY!\n");
    return;
  }

  printf("task to be added, ");
  fgets(new->objective,MAX,stdin);
  new->objective[strcspn(new->objective,"\n")]='\0';

  new->num = count;
  count++;
  new->status = 0;
  new->next = NULL;
  
  if (*list == NULL) {
    *list=new;
    printf("added succesfully :)\n");
    return;
  }
  else {
    node *last = *list;
    while (last->next != NULL) {
      last=last->next;
    }
    last->next = new;
  }

  printf("added succesfully :)\n");
}

void print_all(node *list) {
  if (list == NULL) {
    printf("nothing to display, try adding tasks first.\n");
    return;
  }
  node *chad=list;
  while (chad != NULL) {
    printf("%d. [%c] %s\n",chad->num,chad->status == 0?'X':'O',chad->objective);
    chad=chad->next;
  }
}

void releasing(node *list) {
  while (list != NULL) {
    node *eraser=list->next;
    free(list);
    list=eraser;
  }
}

void remove_task(node **list) {
  int choice;

  do {
    printf("which task you wanna delete? ");
    scanf("%d",&choice);
    getchar();

    if (choice > count || choice < 0) {
      printf("please enter a valid task number.\n");
    }
  } while(choice > count || choice < 0);

  node *next=*list;
  node *prev=NULL;


  if (next->num == choice) {
    *list=next->next;
    free(next);
    node *temp=*list;
    while(temp != NULL) {
      temp->num -= 1;
      temp=temp->next;
    }
  } else {
    while (next->next != NULL && next->num != choice) {
      prev=next;
      next=next->next;
    }

    if (next == NULL) {
      printf("%d task not found.\n",choice);
      return;
    }

    prev->next=next->next;
    free(next);
    prev=prev->next;

    while(prev != NULL) {
      prev->num -= 1;
      prev=prev->next;
    }
 }
  printf("task number %d, deleted succesfully.\n",choice);
}

void update_status(node *list) {
  int user_choice;
  do {
    printf("which task did you complete? ");
    scanf("%d",&user_choice);
    getchar();

    if (user_choice > count || user_choice < 0) {
      printf("please enter a valid task number\n");
    }
  }

  node *chad = list;
  while (chad->num != user_choice && chad->next != NULL) {
    printf("%d\n",chad->num);
    chad=chad->next;
  }

  if (chad->next == NULL) {
    printf("%d task not found.\n",user_choice);
    return;
  }

  chad->status = 1;
  printf("updated %d task to completed.\n");
}

