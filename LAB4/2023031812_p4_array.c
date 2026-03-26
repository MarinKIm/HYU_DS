#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 10

typedef int ElementType;
typedef struct StackRecord *Stack;

typedef struct StackRecord{
    ElementType *key;
    int top;
    int max_stack_size;
 } StackRecord;


Stack CreateStack(void){
    Stack S;

    S=malloc(sizeof(struct StackRecord));
    if(S==NULL){
        printf("\nError: Out of Space!!!\n");
        exit(1);
    }
    S->key = malloc(sizeof(int)*MAX_STACK_SIZE);
    if(S->key == NULL){
        printf("\nError: Out of Space!!!\n");
    }
    S->top = -1;
    S->max_stack_size = MAX_STACK_SIZE;
    return S;
}

int IsEmpty(Stack S){
    if(S->top == -1){
        return 1;
    }
    else{
        return 0;
    }
    
}

void PrintStack(Stack S){
    if(IsEmpty(S)){
        printf("\nStack is empty!\n");
        return;
    }

    printf("Current Stack:");
    for(int i=S->top; i >=0 ;i--){
        printf(" %d",S->key[i]);
    }
    printf("\n");
}

int IsFull(Stack S){
    if(S->top == MAX_STACK_SIZE-1){
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
    else{
        S->key[++S->top]=X;
        PrintStack(S);
    }
}

int Pop(Stack S){
    if(IsEmpty(S)){
        printf("\nStack Underflow!\n");
        exit(1);
    }
    else{
        return S->key[S->top--];
    }
}

void MakeEmpty(Stack S){
    S->top = -1;
}

void DeleteStack(Stack S){
    MakeEmpty(S);
    free(S->key);
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
            case '+': result = b+a; break;
            case '-': result = a-b; break;
            case '*': result = b*a; break;
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
