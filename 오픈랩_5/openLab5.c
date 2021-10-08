#include <stdio.h>
#include<stdlib.h>


typedef struct list_node *list_pointer;

typedef struct list_node {
    int data;
    list_pointer link;
} list_node;


void insert_last(list_pointer *ptr, list_pointer node);
int length(list_pointer ptr);
void print(list_pointer node);
void append(list_pointer* dest, list_pointer* source);
void delete(list_pointer* from, int num);

int main(void) {
    FILE* fp = fopen("A.txt", "r");
    
    list_pointer ALast = NULL;
    int a;
    list_pointer BLast = NULL;
    int b;
    list_pointer CLast = NULL;
    int c;
    list_pointer temp;
    
    while (fscanf(fp, "%d", &a) != EOF) {
        list_pointer new = (list_pointer) malloc(sizeof(list_node));
        
        new->data = a;
        new->link = NULL;
        
        insert_last(&ALast, new);
    }
    fclose(fp);
    
    
    fp = fopen("B.txt", "r");
    
    while (fscanf(fp, "%d", &b) != EOF) {
        list_pointer new = (list_pointer) malloc(sizeof(list_node));
        
        new->data = b;
        new->link = NULL;
        
        insert_last(&BLast, new);
    }
    fclose(fp);

    append(&ALast, &BLast);
    print(ALast);
    
    
    fp = fopen("C.txt", "r");
    
    while (fscanf(fp, "%d", &c) != EOF) {
        list_pointer new = (list_pointer) malloc(sizeof(list_node));
        
        new->data = c;
        new->link = NULL;
        
        insert_last(&CLast, new);
    }
    fclose(fp);
    
    //print(CLast);
    
    temp = CLast->link;
    for(int i=0; i<length(CLast); i++){
        c = temp->data;
        delete(&ALast, c);
        temp = temp-> link;
    }
  
    print(ALast);
    
    return 0;
}


void insert_last(list_pointer *last, list_pointer node){
     if (!(*last)) {
         *last = node;
         node->link = node;
     }
     else {
         node->link = (*last)->link;
         (*last)->link = node;
         *last = node;
     }
    
}

int length(list_pointer ptr) {
    list_pointer temp;
    int count = 0;
    if (ptr) {
        temp = ptr;
        do {
            count++;
            temp = temp->link;
            
        } while (temp != ptr);
    }
    return count;
    
}

void print(list_pointer node) {
    list_pointer temp;
    temp = node -> link;
    int p;
    //printf("%d\n", length(node));
    for(int i=0; i<length(node); i++){
        p = temp -> data;
        printf("%d ", p);
        temp = temp ->link;
    }
    printf("\n");
}


void append(list_pointer* dest, list_pointer* source) {
    list_pointer temp;
    temp = (*source)->link;
    for(int i=0; i<length(*source); i++){
        list_pointer new = (list_pointer) malloc(sizeof(list_node));
        new->data = temp->data;
        new->link = NULL;
        
        insert_last(dest, new);
        temp = temp->link;
    }
 
}


void delete(list_pointer* from, int num){
    
    list_pointer prev = (*from);
    list_pointer del;
    list_pointer temp = (*from) -> link;
    
    int len = length(*from);
    
    for(int i=0; i<len; i++){
        //printf("!%d\n", i);
        if (num == temp->data){
            //printf("%d %d\n", num, temp->data);
            prev->link = temp->link;
            del = temp;
            temp = temp ->link;
            free(del);
            if(i == len-1)
                (*from) = prev;
        }
        else{
            prev = temp;
            temp = temp->link;
        }
    }
}
