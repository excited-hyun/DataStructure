#include <stdio.h>
#include <stdlib.h>

typedef struct threadedTree *threadedPointer;
typedef struct threadedTree {
    short int leftThread;
    threadedPointer leftChild;
    char data;
    threadedPointer rightChild;
    short int rightThread;
} threadedTree;

threadedPointer insucc(threadedPointer tree);

void tinorder(threadedPointer tree);

void insertRight(threadedPointer s, threadedPointer r);
void insertLeft(threadedPointer s, threadedPointer l);
threadedPointer getNewNode(char data) ;

int main() {
    /* image 5.23 */
    threadedPointer root = getNewNode('-');
    insertLeft(root, getNewNode('A'));
    insertLeft(root->leftChild, getNewNode('B'));
    insertLeft(root->leftChild->leftChild, getNewNode('D'));
    insertLeft(root->leftChild->leftChild->leftChild, getNewNode('H'));
    insertRight(root->leftChild->leftChild->leftChild, getNewNode('I'));
    insertRight(root->leftChild->leftChild, getNewNode('E'));
    insertRight(root->leftChild, getNewNode('C'));
    insertLeft(root->leftChild->rightChild, getNewNode('F'));
    insertRight(root->leftChild->rightChild, getNewNode('G'));
    //printf("a\n");
    tinorder(root);
    return 0;
    
}

threadedPointer insucc(threadedPointer tree)
{
/* find the inorder successor of tree
in a threaded binary tree */
    threadedPointer temp;
    temp = tree->rightChild;
    
    if (!tree->rightThread)
        while (!temp->leftThread)
            temp = temp->leftChild;
    
    return temp;
    
}

void tinorder(threadedPointer tree) {
    /* traverse the threaded binary tree inorder */
    threadedPointer temp = tree;
    for ( ; ; ) {
        temp = insucc(temp);
        if (temp == tree)
            break;
        printf("%3c", temp->data);
    }
    printf("\n");
}

void insertRight(threadedPointer parent, threadedPointer child) {
    /* insert child as the right child of parent in a threaded binary tree */
    threadedPointer temp;
    
    child->rightChild = parent->rightChild;
    child->rightThread = parent->rightThread;
    child->leftChild = parent;
    child->leftThread = 1;
    parent->rightChild = child;
    parent->rightThread = 0;
    
    if (!child->rightThread) {
        temp = insucc(child);
        temp->leftChild = child;
    }
    
}

void insertLeft(threadedPointer parent, threadedPointer child) {
    /* insert child as the right child of parent in a threaded binary tree */
    threadedPointer temp;
    
    child->leftChild = parent->leftChild;
    child->leftThread = parent->leftThread;
    child->rightChild = parent;
    child->rightThread = 1;
    parent->leftChild = child;
    parent->leftThread = 0;
    
    if (!child->leftThread) {
        temp = insucc(child);
        temp->rightChild = child;
    }
}

threadedPointer getNewNode(char data) {
    
    threadedPointer new = (threadedPointer)malloc(1*sizeof(threadedTree));

    new->leftChild = new;
    new->rightChild = new;
    new->leftThread = 1;
    new->rightThread = 0;
    new->data = data;
    
    return new;
}
