#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
int failure[MAX];
int kmp_cnt;
int nfind_cnt;

int nfind(char *string, char *pat){
    
    int i, j, start = 0;
    int lasts = strlen(string)-1;
    int lastp = strlen(pat)-1;
    int flag = 0;
    
    int endmatch = lastp;
    
    
    for (i = 0; endmatch <= lasts; endmatch++, start++) {
        flag = 0;   //끝값이 같은 경우 안쪽 for문에 들어가지않아 nfind_cnt값이 증가되지 않는 문제 해결위한 flag
        
        if (string[endmatch] == pat[lastp]) {
            flag = 1;
            for (j=0, i=start; j < lastp && string[i] == pat[j]; i++, j++) {
                nfind_cnt++;
            }
        }
        if(flag == 0)   //끝값 달라서 안쪽 for문에 못들어간 경우 nfind_cnt++
            nfind_cnt++;
        
        if (j == lastp) {   //성공
            return start;
        }
    }
    
    return -1;
}

int pmatch(char * string, char *pat)
{
    int i = 0,j = 0;
    int lens = strlen(string);
    int lenp = strlen(pat);
    while (i < lens && j < lenp)
    {
        kmp_cnt++;
        //pattern 일치
        if (string[i] == pat[j])
        {
            i++;
            j++;
        }
        //pattern이 하나도 일치하지 않음
        else if (j == 0)
            i++;
        else //pattern 일치하는 부분까지
            j = failure[j - 1] + 1;
    }
    
    return ((j == lenp) ? (i - lenp) : -1);
}

void fail(char *pat)
{
    int n = strlen(pat);
    int i,j;
    failure[0] = -1;
    for (j = 1; j < n; j++)
    {
        i = failure[j - 1];
        while ((pat[j] != pat[i + 1]) && (i >= 0))
        {
            i = failure[i];
        }
        if (pat[j] == pat[i + 1])
            failure[j] = i + 1;// 중복 될 시 앞에것에 +1
        else failure[j] = -1; //중복 없을 시 -1
        
    }
}

int main()
{
    FILE* fp1;
    char string[MAX];
    char pat[MAX];
    int matched;
    
    fp1 = fopen("input.txt","r");
    
    if(!fp1)
    {
        printf("Input FIle Error!\n");
        exit(1);
    }
    fscanf(fp1, "%s", string);
    fscanf(fp1, "%s", pat);
    //printf("%s!\n",string);
    //printf("%s!\n",pat);
    fail(pat);
    
    matched = nfind(string, pat);
    if(matched == -1)
        printf("NO %d\n", nfind_cnt);
    else
        printf("YES %d\n", nfind_cnt);
    
    
    matched = pmatch(string,pat);
    if(matched == -1)
        printf("NO %d\n", kmp_cnt);
    else
        printf("YES %d\n", kmp_cnt);
    
}





