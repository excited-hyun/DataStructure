#define MAX_TERMS 101
#define MAX_COL 10

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int col;
    int row;
    int value;
}term;

void fastTranspose(term a[], term b[]);
void printMat(term *d, term *d_trans);
void Add(term a[], term b[]);

term d[MAX_TERMS];

int main()
{
    term a[MAX_TERMS], b[MAX_TERMS];
    term d_trans[MAX_TERMS];

    FILE *fp1, *fp2;
    int n1, n2, m1, m2; // 'm'은 행, 'n'은 열의 갯수
    int a_cnt = 0, b_cnt=0; // non-zero term의 갯수
    int temp1, temp2;
    
    fp1 = fopen("A.txt", "r");
    fp2 = fopen("B.txt", "r");
    if(!fp1 || !fp2)
    {
        printf("Input FIle Error!\n");
        exit(1);
    }
    
    fscanf(fp1, "%d %d", &n1, &m1);
    fscanf(fp2, "%d %d", &n2, &m2);
    
    
    // 초기화(row major order, 3-tuple)
    a[0].row = n1;
    a[0].col = m1;
    b[0].row = n2;
    b[0].col = m2;
    
    for(int i=0;i<n1*m1;i++)
    {
        fscanf(fp1, "%d", &temp1);
        fscanf(fp2, "%d", &temp2);
        
        if(temp1 != 0){
            a_cnt++;
            a[a_cnt].row = i/m1;
            a[a_cnt].col = i%m1;
            a[a_cnt].value = temp1;
            
        }
        
        if(temp2 != 0){
            b_cnt++;
            b[b_cnt].row = i/m2;
            b[b_cnt].col = i%m2;
            b[b_cnt].value = temp2;
          
        }
    }
    a[0].value = a_cnt;
    b[0].value = b_cnt;
    
    //printf("Matrix Addition:\n");
    Add(a, b);
    
   // printMat(d);
    
    //printf("\nTranspose Matrix:\n");
    fastTranspose(d, d_trans);
    printMat(d, d_trans);
    
    return 0;
}

void fastTranspose(term a[], term b[])
{ /* the transpose of a is placed in b */

    int temp1, temp2;
    int row_terms[MAX_COL];
    int i, j, num_cols = a[0].col, num_terms = a[0].value;
    b[0].row = num_cols;
    b[0].col = a[0].row;
    b[0].value = num_terms;
    
  
    if (num_terms > 0) { /* nonzero matrix */

        for (i = 0; i < num_cols; i++)
            row_terms[i] = 0;

        for (i = 1; i <= num_terms; i++)
            row_terms[a[ i ].col]++;
        
        temp1 = 1;
        
        for(i = 0; i < num_cols; i++) {
            temp2 = row_terms[i];
            row_terms[i] = temp1;
            temp1 += temp2;
        }
        
        for(i=1; i<=num_terms; i++) {
        
            j = row_terms[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
        
        
    }
}

void printMat(term *d, term *d_trans)
{
    printf("Matrix Addition:\t\t");
    printf("Transpose Matrix:\n");
    for(int i=0;i<=d[0].value;i++){
        printf("%d %d %d\t\t\t\t", d[i].row, d[i].col, d[i].value);
        printf("%d %d %d\n", d_trans[i].row, d_trans[i].col, d_trans[i].value);
    }
}


void Add(term a[], term b[]){

    int a_i=1, b_i=1, d_i=1;
    // 크기가 같은지를 확인
    if((a[0].row != b[0].row) || (a[0].col != b[0].col))
    {
        printf("A and B is not same size!\n");
        exit(1);
    }
        
    d[0].row = a[0].row;
    d[0].col = a[0].col;

    while( a_i <= a[0].value && b_i <= b[0].value ){
        //fill in matrix D by comparing row and columns
        if (a[a_i].row == b[b_i].row) {
            if (a[a_i].col == b[b_i].col) {
                d[d_i].row = a[a_i].row;
                d[d_i].col = a[a_i].col;
                d[d_i].value = a[a_i].value + b[b_i].value;
                d_i++;
                a_i++;
                b_i++;
            }
            else if (a[a_i].col < b[b_i].col) {
                d[d_i].row = a[a_i].row;
                d[d_i].col = a[a_i].col;
                d[d_i].value = a[a_i].value;
                d_i++;
                a_i++;
            }
            else {
                d[d_i].row = b[b_i].row;
                d[d_i].col = b[b_i].col;
                d[d_i].value = b[b_i].value;
                d_i++;
                b_i++;
            }
        }
        else if (a[a_i].row < b[b_i].row) {
            d[d_i].row = a[a_i].row;
            d[d_i].col = a[a_i].col;
            d[d_i].value = a[a_i].value;
            d_i++;
            a_i++;
        }
        else {
            d[d_i].row = b[b_i].row;
            d[d_i].col = b[b_i].col;
            d[d_i].value = b[b_i].value;
            d_i++;
            b_i++;
        }
    }
    
    for (; a_i <= a[0].value; a_i++) {
        d[d_i].row = a[a_i].row;
        d[d_i].col = a[a_i].col;
        d[d_i].value = a[a_i].value;
        d_i++;
        a_i++;
        }
        
    for (; b_i <= b[0].value; b_i++) {
        d[d_i].row = b[b_i].row;
        d[d_i].col = b[b_i].col;
        d[d_i].value = b[b_i].value;
        d_i++;
        b_i++;
    }
    
    d[0].value = d_i-1;

}
