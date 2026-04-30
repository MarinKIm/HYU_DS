#include <stdio.h>
#include <stdlib.h>

struct TreeStruct{
    int size;
    int numOfNode;
    int* element;

};

typedef struct TreeStruct* Tree;

Tree CreateTree(int size){
    Tree T = (Tree)malloc(sizeof(struct TreeStruct));
    T->element = (int*)malloc(sizeof(int)*(size+1));
    T->size = size;
    T->numOfNode = 0;
    
    return T;
}

void Insert(Tree tree, int value){
    if(tree->numOfNode >= tree->size){
        printf("Error! Tree is full.\n");
    }
    else{
        tree->element[++tree->numOfNode] = value;
    }
}

void PrintPreorder(Tree tree, int index){
    if(index > tree->numOfNode){
        return;
    }
    printf("%d ",tree->element[index]);
    PrintPreorder(tree, index*2);
    PrintPreorder(tree, index*2+1);
}

void PrintInorder(Tree tree, int index){
    if(index > tree->numOfNode){
        return;
    }
    PrintInorder(tree, index*2);
    printf("%d ",tree->element[index]);
    PrintInorder(tree, index*2+1);

}

void PrintPostorder(Tree tree, int index){
    if(index > tree->numOfNode){
        return;
    }
    PrintPostorder(tree, index*2);
    PrintPostorder(tree, index*2+1);
    printf("%d ",tree->element[index]);
    
}

int CountLeafNodes(Tree tree, int index){
    if(index > tree->numOfNode){        // 초과
        return 0;
    }
    if(index * 2 > tree->numOfNode){     //자식이 없음 = leaf
        return 1;
    }
    
    int left  = CountLeafNodes(tree, index * 2);
    int right = CountLeafNodes(tree, index * 2 + 1);
    
    return left + right;
}

int ComputeHeight(Tree tree, int index){
    if(index > tree->numOfNode){
        return 0;
    }
    int result = ComputeHeight(tree, index*2); //array implementation으로 complete binary tree
    
    return result +1 ;
    
}

int isPerfectTree(Tree tree){
    int result = 1;
    for(int i=0;i<ComputeHeight(tree,1)-1;i++){
        result*=2;
    }
    if(CountLeafNodes(tree,1) == result){
        return 1;
    }
    else{
        return 0;
    }
}

void PrintTree(Tree tree){
    printf("Preorder: ");
    PrintPreorder(tree,1);
    printf("\n");
    printf("Inorder: ");
    PrintInorder(tree,1);
    printf("\n");
    printf("Postorder: ");
    PrintPostorder(tree,1);
    printf("\n");
    printf("Leaf Nodes: %d\n",CountLeafNodes(tree,1));
    printf("Tree Height: %d\n",ComputeHeight(tree,1)-1);
    printf("Is Perfect Binary Tree: ");
    if(isPerfectTree(tree) == 1){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
}


void deletetree(Tree tree){
    free(tree->element);
    free(tree);
}

int main(int argc, char**argv){

    FILE *fi;
    Tree tree;
    int treeSize;
    int tmpNum;

    fi = fopen(argv[1], "r");
    fscanf(fi, "%d", &treeSize);
    tree = CreateTree(treeSize);

    while(fscanf(fi, "%d", &tmpNum)==1){
        Insert(tree, tmpNum);
    }
    PrintTree(tree);
    deletetree(tree);
}
