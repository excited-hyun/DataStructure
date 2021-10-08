#include <stdio.h>
#include <stdlib.h>

typedef struct {
        int key;
} element;

typedef struct stack *stackPointer;

typedef struct stack {
        element data;   
        stackPointer link;
} stack;

typedef struct queue *queuePointer;

typedef struct queue {
        element data;    
        queuePointer link;
} queue;


stackPointer top;
queuePointer front, rear;

void stack_push(int input);
int stack_pop(int *out);
void queue_push(int input);
int queue_pop(int *out);

    
int main(void){
    FILE *ofp = fopen("input.txt", "r");
        
    int option, input, out;
    
    while (fscanf(ofp, "%d", &option) != EOF) {
        if (option == 0) {
            fscanf(ofp, "%d", &input);
            stack_push(input);
            queue_push(input);
            
        } 

        else {
            stack_pop(&out);
            queue_pop(&out);
            
        }
    }

              
    while(stack_pop(&out) != 0)    
        printf("%d ", out);
    printf("\n");

    
    while(queue_pop(&out) != 0)
        printf("%d ", out);
    printf("\n");
}


void stack_push(int input){
        
    stackPointer new = (stackPointer) malloc(sizeof(stack));
    
    new->data.key = input;
    new->link = top;
    top = new;
}

int stack_pop(int *out){
        
    if (top == NULL) 
        return 0;
    
    stackPointer del;
    
    *out = top->data.key;

    del = top;
    top = top->link;
    free(del);

    return 1;
}

void queue_push(int input){
        
    queuePointer new = (queuePointer) malloc(sizeof(queue));
    new->link = NULL;
    new->data.key = input;

    
    if (front == NULL) {
        front = new;
        rear = new;
    } 
    
    else {
        rear->link = new;
        rear = rear->link;
    }
}

int queue_pop(int *out){
    if (front == NULL) 
        return 0;
    
    queuePointer del = front;
    
    *out = front->data.key;
    
    front = front->link;
    free(del);
    
    return 1;
}

        
