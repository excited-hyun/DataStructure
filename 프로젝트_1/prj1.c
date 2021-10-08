#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct student{
    char id[10];
    char name[40];
    char course[40];
    int score;
}STUDENT;

typedef struct _treenode{
    STUDENT key;
    struct _treenode *left, *right;
}TreeNode;

int InsertNode(TreeNode* root, STUDENT key);
int DeleteNode(TreeNode* root, char *id);
void SearchCourse(TreeNode* node, char *course);
void SearchName(TreeNode* node, char *name);
int SearchID(TreeNode* node, char *id);

//추가한 함수들
void printMenu(void);       //사용 가능한 메뉴 출력
void inorderPrint(TreeNode* tree);
void preorderPrint(FILE* ofp, TreeNode* tree);      //preorder로 출력하는 함수
void buildTree(TreeNode** root, STUDENT key);       //처음에 트리를 빌드하는데 사용
void addScore(TreeNode* node, char *course, int *cnt, int *score);  //course의 score 계산
TreeNode* modifiedSearch(TreeNode* tree, STUDENT key);      //삽입할 위치 찾는 함수
TreeNode* SearchSame(TreeNode* tree, char* id);     //해당 id갖는 노드 찾는 함수

void inorderPrint(TreeNode* tree) {
    if (tree->left != NULL) {
        inorderPrint(tree->left);
    }
    printf("%s ", tree->key.id);
    if (tree->right != NULL) {
        inorderPrint(tree->right);
    }
}

int main() {
    
    char in_id[10];
    char in_name[40];
    char in_course[40];
    int in_score;
    
    int menu;
    int flag;
    char del_id[10];
    char search_course[40];
    char search_name[40];
    char search_id[10];
    
    FILE* fp = fopen("input.txt", "r");
    
    TreeNode* root = NULL;
    
    //input.txt 읽어옴
    while(fscanf(fp, "%s %s %s %d", in_id, in_name, in_course, &in_score)!=EOF) {
        
        STUDENT* new_student = (STUDENT*) malloc(sizeof(STUDENT));
        strcpy(new_student->id, in_id);
        strcpy(new_student->name, in_name);
        strcpy(new_student->course, in_course);
        new_student->score = in_score;
        
        buildTree(&root, *new_student); //트리에 하나씩 넣으면서 빌드
    }
    
    fclose(fp);
    
    FILE *ofp = fopen("input.txt", "w");

    //inorderPrint(root);
    //printf("\n");
    preorderPrint(ofp, root);
    fclose(ofp);
    //printf("\n");
    
    //사용자가 원하는 메뉴 입력 받아 해당 메뉴 수행
    while(1){
        printMenu();
        scanf("%d", &menu);
        
        if(menu == 1){      //insert
            printf("Input Studebt ID, Name, Course, Score :\n");
            scanf("%s %s %s %d", in_id, in_name, in_course, &in_score);
            
            STUDENT* new_student = (STUDENT*) malloc(sizeof(STUDENT));
            strcpy(new_student->id, in_id);
            strcpy(new_student->name, in_name);
            strcpy(new_student->course, in_course);
            new_student->score = in_score;
            
            flag = InsertNode(root, *new_student);
            
            if(flag)    //성공
                printf("Insert Success!\n");
                
            else        //실패
                printf("This ID already exist!\n");
            
            //inorderPrint(root);
            //printf("\n");
            //ofp = fopen("input.txt", "w");
            //preorderPrint(ofp, root);
            //fclose(ofp);
        }
        
        else if (menu == 2){    //delete
            printf("Input Student ID that you want to delete :\n");
            scanf("%s", del_id);
            flag = DeleteNode(root, del_id);
            
            if(flag)        //성공
                printf("Delete Success!\n");
                
            else            //실패
                printf("Delete Fail!\n");
            
            //inorderPrint(root);
            //printf("\n");
            //ofp = fopen("input.txt", "w");
            //preorderPrint(ofp, root);
            //fclose(ofp);
        }
        
        else if (menu == 3){    //search Course
            printf("Input Course that you want to search :\n");
            scanf("%s", search_course);
            SearchCourse(root, search_course);
        }
        
        else if (menu == 4){    //search Name
            printf("Input Student Name that you want to search :\n");
            scanf("%s", search_name);
            SearchName(root, search_name);
        }
        
        else if (menu == 5){    //search ID
            printf("Input Student ID that you want to search :\n");
            scanf("%s", search_id);
            flag = SearchID(root, search_id);
            
            if(flag)        //성공
                printf("Search by ID Success!\n");
            else            //실패
                printf("Search by ID Fail!\n");
        }
        
        else if (menu == 6){    //exit
            printf("Bye!!\n");
            //printf("\n");
            ofp = fopen("input.txt", "w");
            preorderPrint(ofp, root);
            fclose(ofp);
            return 0;
        }
        
        else{       //잘못된 메뉴
            printf("Wrong Menu!\n");
        }
    }
    
    
    return 0;
}

void printMenu(void){
    
    printf("\n+++++++++++++++++++++++++++++++++++++++\n");
    printf("1. Insert new student\n");
    printf("2. Delete student\n");
    printf("3. Search course\n");
    printf("4. Search student by name\n");
    printf("5. Search student by ID\n");
    printf("6. Save in input.txt and Exit\n");
    printf("+++++++++++++++++++++++++++++++++++++++\n");
    printf("Input the number of Menu (1 ~ 6) >> ");
}

void buildTree(TreeNode** root, STUDENT key){
    //printf("%s %s %s %d\n", key.id, key.name, key.course, key.score);
    
    TreeNode *ptr, *temp = modifiedSearch(*root, key);
    int num1, num2;
    
    if (temp || !(*root)) {
        
        ptr = (TreeNode*) malloc(sizeof(TreeNode));
        if (ptr == NULL) {
            printf("Memory is Full!\n");
            exit(1);
        }
        ptr->key = key;
        ptr->left = ptr->right = NULL;
        
        if (*root) {
            num1 = atoi(key.id);
            num2 = atoi(temp->key.id);
            
            if(num1 < num2){
                temp->left = ptr;
                //printf("left %s\n", ptr->key.id);
            }
            else if(num1 > num2){
                temp->right = ptr;
                //printf("right %s\n", ptr->key.id);
            }
        }
        else
            *root = ptr;
    }
}

TreeNode* modifiedSearch(TreeNode* tree, STUDENT key) {
    TreeNode* last = NULL;
    int num1, num2;
    num1 = atoi(key.id);
    while (tree) {
        num2 = atoi(tree->key.id);
        if (num1 == num2)
            return NULL;
        else if (num1 < num2) {
            last = tree;
            tree = tree->left;
        }
        else {
            last = tree;
            tree = tree->right;
        }
    }
    return last;
}


void preorderPrint(FILE* ofp, TreeNode* tree) {
    
    fprintf(ofp, "%s %s %s %d\n", tree->key.id, tree->key.name, tree->key.course, tree->key.score);
    //printf("%s ", tree->key.id);
    if (tree->left != NULL) {
        preorderPrint(ofp, tree->left);
    }
    if (tree->right != NULL) {
        preorderPrint(ofp, tree->right);
    }
}


int InsertNode(TreeNode* root, STUDENT key) {
    
    TreeNode *ptr, *temp = modifiedSearch(root, key);
    int num1, num2;
    
    if(temp == NULL)
        return 0;
    
    else{
        ptr = (TreeNode*) malloc(sizeof(TreeNode));
        if (ptr == NULL) {
            printf("Memory is Full!\n");
            exit(1);
        }
        ptr->key = key;
        ptr->left = ptr->right = NULL;
        
        if (root) {
            num1 = atoi(key.id);
            num2 = atoi(temp->key.id);
            
            if(num1 < num2){
                temp->left = ptr;
                //printf("left %s\n", ptr->key.id);
            }
            else if(num1 > num2){
                temp->right = ptr;
                //printf("right %s\n", ptr->key.id);
            }
        }
    }
    return 1;
}


int DeleteNode(TreeNode* root, char *id){
    TreeNode *search, *parent, *temp;
    STUDENT temp_key;
    
    int num1, num2;
    int flag=0;
    num1 = atoi(id);
    parent = NULL;
    search = root;
    
    while(search){      //노드 검색
        num2 = atoi(search->key.id);
        if (num1 == num2)
            break;
        
        parent = search;
        
        if (num1 < num2) {
            search = search->left;
        }
        else {
            search = search->right;
        }
    }
    
    if(search == NULL)  //해당 값 존재X
        return 0;
    //printf("a\n");
    
    if(search->left && search->right)   //자식 노드 2개
    {
        //printf("two child\n");
        parent = search;
        temp = search;
        search = search->left;
       
        while(search->right){
            temp = search;
            search = search->right;
            //flag = 1;
        }
        
        temp_key = search->key;
        DeleteNode(parent,search->key.id);
        parent->key = temp_key;
        /*if(flag)
            temp->right = NULL;
        else
            temp->left = NULL;*/
     
        //free(search);
    }
    
    else if(search->left || search->right)  //자식 노드 1개
    {
        //printf("one child\n");
        if(search->left)
            temp = search->left;
        else
            temp = search->right;
        
        if(parent!=NULL){
            if(parent->left == search)
                parent->left = temp;
            else
                parent->right = temp;
            free(search);
        }
        else{
            if(search->left){
                temp = search;
                search = search->left;
                while(search->right){
                    temp = search;
                    search = search->right;
                    //flag = 1;
                }
                temp_key = search->key;
                DeleteNode(root,search->key.id);
                root->key = temp_key;
                /*
                if(flag)
                    temp->right = NULL;
                else
                    temp->left = NULL;
                */
            }
            else{
                temp = search;
                search = search->right;
                while(search->left){
                    temp = search;
                    search = search->left;
                    //flag = 1;
                }
                temp_key = search->key;
                DeleteNode(root,search->key.id);
                root->key = temp_key;
                /*
                if(flag)
                    temp->left = NULL;
                else
                    temp->right = NULL;*/
            }
        }
        //free(search);
    }
    
    else        //자식 노드 0개
    {
        //printf("no child\n");
        if(parent->left == search)
            parent->left = NULL;
        else
            parent->right = NULL;
        free(search);
    }
    
    
    
    
    return 1;
}

TreeNode* SearchSame(TreeNode* tree, char* id){

    int num1, num2;
    num1 = atoi(id);
    
    while (tree) {
        num2 = atoi(tree->key.id);
        if (num1 == num2)
            return tree;
        else if (num1 < num2) {
            tree = tree->left;
        }
        else {
            tree = tree->right;
        }
    }
    return NULL;
}

void SearchCourse(TreeNode* node, char *course){
    int cnt = 0;
    int sum_score = 0;
    addScore(node, course, &cnt, &sum_score);
    if(cnt == 0){
        printf("There are no student taking that coourse!");
        return;
    }
    printf("=====================================\n");
    printf("Average : %.4f\n", (float)sum_score / (float)cnt);
}

void addScore(TreeNode* node, char *course, int *cnt, int *score){
    if(strcmp(node->key.course, course) == 0 && strlen(node->key.course) == strlen(course)){
        printf("=====================================\n");
        printf("ID: %s\n", node->key.id);
        printf("Name: %s\n", node->key.name);
        printf("Course: %s\n", node->key.course);
        printf("Score: %d\n", node->key.score);
        (*cnt)++;
        *score += node->key.score;
    }
    if (node->left != NULL) {
        addScore(node->left, course, cnt, score);
    }
    if (node->right != NULL) {
        addScore(node->right, course, cnt, score);
    }
}

int SearchID(TreeNode* node, char *id){
    TreeNode * temp = SearchSame(node, id);
    
    if(temp == NULL)
        return 0;
    printf("ID: %s\n", temp->key.id);
    printf("Name: %s\n", temp->key.name);
    printf("Course: %s\n", temp->key.course);
    printf("Score: %d\n", temp->key.score);
    
    return 1;
}

void SearchName(TreeNode* node, char *name){
    if(strcmp(node->key.name, name) == 0 && strlen(node->key.name) == strlen(name)){
        printf("=====================================\n");
        printf("ID: %s\n", node->key.id);
        printf("Name: %s\n", node->key.name);
        printf("Course: %s\n", node->key.course);
        printf("Score: %d\n", node->key.score);
    }
    if (node->left != NULL) {
        SearchName(node->left, name);
    }
    if (node->right != NULL) {
        SearchName(node->right, name);
    }
}
