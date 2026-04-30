#include<stdio.h>
#include<stdlib.h>

typedef struct BinarySearchTree* Tree;
struct BinarySearchTree{
    int value;
    Tree left;
    Tree right;
};

Tree insertNode(Tree root, int key){
    if(root == NULL){
        root = (Tree)malloc(sizeof(struct BinarySearchTree));
        if(root == NULL){
            return NULL;                         
        }
        else{
            root->value = key;
            root->left = root->right = NULL;
            printf("Insert %d\n", key);
        }
    }
    else if(root->value == key){                  
        printf("Insertion Error: There is already %d in the tree\n", key);
    }
    else if(key < root->value){
        root->left = insertNode(root->left, key);
    }
    else if(key > root->value){
        root->right = insertNode(root->right, key);
    }
    return root;
}

Tree findMin(Tree root){
    if(root == NULL){
        return NULL;
    }
    else if(root->left == NULL){
        return root;
    }
    else{
        return findMin(root->left);
    }
}                                                 
Tree findMax(Tree root){
    if(root == NULL){
        return NULL;
    }
    else if(root->right == NULL){
        return root;
    }
    else{
        return findMax(root->right);
    }
}                                                

Tree deleteNode(Tree root, int key){
    static int pp = 0;
    static int cd = 0;
    Tree tmp;

    if(cd == 0){
        pp = 0;   
    }
    cd++;

    if(root == NULL){
        if(!pp){
            printf("Deletion Error: %d is not in the tree\n", key);
            pp = 1;
        }
        cd--;
        return NULL;
    }

    if(key < root->value){
        root->left = deleteNode(root->left, key);
    }
    else if(key > root->value){
        root->right = deleteNode(root->right, key);
    }
    else{
        if(!pp){
            printf("Delete %d\n", key);  
            pp = 1;
        }

        if(root->left && root->right){
            tmp = findMax(root->left);
            int maxVal = tmp->value;
            root->left = deleteNode(root->left, maxVal);
            root->value = maxVal;
        }
        else{
            tmp = root;
            if(root->left == NULL){
                root = root->right;
            }
            else{
                root = root->left;
            }
            free(tmp);
        }
    }

    cd--;   
    return root;
}

int getHeight(Tree root){
    if(root == NULL){
        return -1;
    }
    int right = getHeight(root->right);
    int left  = getHeight(root->left);
    return (right > left ? right : left) + 1;
}

void findNode(Tree root, int key){
    if(root == NULL){
        printf("%d is not in the tree\n", key);
        return;                                  
    }
    if(key < root->value){
        findNode(root->left, key);
    }
    else if(key > root->value){
        findNode(root->right, key);
    }
    else{
        printf("%d is in the tree\n", key);
    }
}

void printInorder(Tree root){
    if(root == NULL) return;                      
    printInorder(root->left);
    printf("%d ", root->value);
    printInorder(root->right);
}

void printPreorder(Tree root){
    if(root == NULL) return;                      
    printf("%d ", root->value);
    printPreorder(root->left);                    
    printPreorder(root->right);
}

void printPostorder(Tree root){
    if(root == NULL) return;                     
    printPostorder(root->left);
    printPostorder(root->right);
    printf("%d ", root->value);
}

int main(int argc, char**argv){
    FILE *fi = fopen(argv[1], "r");
    char cmd;
    int key;

    Tree root = NULL;

    while(!feof(fi)){
        fscanf(fi, " %c", &cmd);                
        switch(cmd){
            case 'i':
                fscanf(fi, "%d", &key);
                root = insertNode(root, key);
                break;
            case 'd':
                fscanf(fi, "%d", &key);
                root = deleteNode(root, key);
                break;
            case 'p':
                fscanf(fi, " %c", &cmd);
                if(cmd == 'i'){
                    printInorder(root);
                }
                else if(cmd == 'r'){
                    printPreorder(root);
                }
                else if(cmd == 'o'){
                    printPostorder(root);
                }
                printf("\n");
                break;
            case 'f':
                fscanf(fi, "%d", &key);
                findNode(root, key);
                break;
            case 'm':
                fscanf(fi, " %c", &cmd);
                if(cmd == 'i'){
                    Tree minNode = findMin(root);
                    if(minNode){
                        printf("Min: %d\n", minNode->value);
                    }
                }
                else if(cmd == 'a'){
                    Tree maxNode = findMax(root);  
                    if(maxNode){
                        printf("Max: %d\n", maxNode->value);
                    }
                }
                break;
            case 'h':
                printf("Height: %d\n", getHeight(root));
                break;
            default:
                break;
        }
    }
    fclose(fi);                                
    return 0;
}