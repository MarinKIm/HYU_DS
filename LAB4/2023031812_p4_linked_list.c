#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 10

typedef struct Node* PtrToNode;
typedef PtrToNode Stack;
typedef PtrToNode Position;
typedef int ElementType;
struct Node{
    ElementType Element;
    PtrToNode Next;
};

Stack CreateStack(void);
int IsEmpty(Stack S);
int IsFull(Stack S);
void Push(ElementType X, Stack S);
int Pop(Stack S);
void MakeEmpty(Stack S);
void DeleteStack(Stack S);
void Postfix(Stack S, char c);

Stack CreateStack(void){
    Stack S;

    S=(Stack)malloc(sizeof(struct Node));
    if(S==NULL){
        printf("Error: Out of Space!!!\n");
        exit(1);
    }
    S->Element = '\0';
    S->Next = NULL;
    return S;

}

int IsEmpty(Stack S){
    if(S->Next == NULL){
        return 1;
    }
    else{
        return 0;
    }
    
}

void PrintStack(Stack S){
    Position P = S->Next;

    if(IsEmpty(S)){
        printf("Stack is empty!\n");
        return;
    }

    printf("Current Stack:");
    while(P!=NULL){
        printf(" %d",P->Element);
        P=P->Next;
    }
    printf("\n");
}

int IsFull(Stack S){
    Position P = S->Next;
    int result = 0;

    while(P!=NULL){
        result++;
        P=P->Next;
    }

    if(result>=MAX_STACK_SIZE){
        return 1;
    }
    else{
        return 0;
    }
}


void Push(ElementType X, Stack S){

    if(IsFull(S)){
        printf("\nStack Overflow!\n");
        exit(1);
    }

    Position TmpCell;

    TmpCell = malloc(sizeof(struct Node));

    if(TmpCell == NULL){
        return;
    }
    TmpCell->Element = X;
    TmpCell->Next = S->Next;
    S->Next = TmpCell;
    PrintStack(S);
}

int Pop(Stack S){

    if(IsEmpty(S)){
        printf("\nStack Underflow!\n");
        exit(1);
    }

    Position P = S->Next;
    int v = P->Element;

    S->Next = P->Next;
    free(P);

    return v;
}

void MakeEmpty(Stack S){
    while(!IsEmpty(S)){
        Pop(S);
    }
}

void DeleteStack(Stack S){
    MakeEmpty(S);
    free(S);
}

void Postfix(Stack S, char c){
    if(isdigit(c)){
        Push(c-'0', S);
    }
    else{
        int b = Pop(S);
        int a = Pop(S);
        int result;

        switch(c){
            case '+': result = a+b; break;
            case '-': result = a-b; break;
            case '*': result = a*b; break;
            case '/': result = a/b; break;
            case '%': result = a%b; break;

            default:
                printf("Invalid operator encountered: %c\n",c);
                exit(1);
        }
        Push(result, S);
    }
}


int main(int argc, char *argv[]) {
        if (argc != 2) {
                printf("Please enter an input file!");
                exit(1);
        }

        FILE *fp = fopen(argv[1], "r");

        if(fp == NULL){
            printf("Error opening file");
            exit(1);
        }

        Stack stack = CreateStack();

        char c;
        while(fscanf(fp, "%c", &c)!= EOF){
            if(c == '#'){
                printf("\nCalculating Done!");
                break;
            }
            Postfix(stack, c);
        }
        printf("\n");
        printf("Evaluation result: %d\n", Pop(stack));
        fclose(fp);
        DeleteStack(stack);

        return 0;
}
