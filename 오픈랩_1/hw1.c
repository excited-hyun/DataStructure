#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 101

clock_t start;


void insertionSort(int* U, int* S, int num)
{
    int i, j;

    for (i = 0; i < num; i++)
    {
        for(j=i-1; j>=0 && U[i] < S[j]; j-- ){
            S[j+1] = S[j];
        }
        S[j+1] = U[i];
    }

}

int main()
{
    
    FILE *fp;
 
    int* U = (int*)malloc (sizeof (int)*MAX);
    int* S = (int*)malloc (sizeof (int)*MAX);

    int i=0;
    int num;
    int step = 10;
    int n;
    double duration;

    fp = fopen("lab1.data", "r");
    
    if(fp == NULL){
        printf("FILE OPEN ERROR!\n");
        return 0;
    }
    
    printf("Input : ");
    
    while( fscanf(fp, "%d", &U[i]) != EOF){
        printf("%d ",U[i]);
        i++;
    }
 
    num = i;
    
    insertionSort(U, S, num);
  
    printf("\nSorted : ");

    for(i= 0; i<num; i++){
        printf("%d ", S[i]);
    }
    free(S);
    free(U);
    
    U = (int*)malloc (sizeof (int)*MAX);
    S = (int*)malloc (sizeof (int)*MAX);
    
    printf("\n     n\t\t  repetitions\t\t  time\n");
    for(n=0; n<=100; n+=step){
        long repetitons = 0;
        clock_t start = clock();
        do{
            repetitons++;
            for(i=0; i<n; i++){
                U[i] = n-i;
            }
            insertionSort(U, S, n);
        }while(clock() - start < 1000);
        
        duration = ((double) (clock()-start))/ CLOCKS_PER_SEC;
        duration /= repetitons;
        printf("%6d\t\t%9ld\t\t%f\n", n, repetitons, duration);
    }
    free(S);
    free(U);
    fclose(fp);
}

