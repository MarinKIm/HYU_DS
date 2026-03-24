#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef char ElementType[256];

struct Node {
        ElementType song;
        Position next;
};

List MakeEmpty(){
        List L;
        L = (List)malloc(sizeof(struct Node));
        L->song[0] = '\0';
        L->next = NULL;
        return L;
}

Position Find(ElementType X, List L){

        Position P;

        P=L->next;
        while(P!=NULL && strcmp(P->song, X) != 0){
                P=P->next;
        }
        return P;
}

Position FindPrevious(ElementType X, List L){

        Position P;

        P=L;
        while(P->next != NULL && strcmp(P->next->song, X) != 0){
                P=P->next;
        }
        return P;
}

void Insert(ElementType X, List L, Position P){
        Position TmpCell;

        TmpCell = malloc(sizeof(struct Node));

        if(TmpCell == NULL){
                return;
        }

        strcpy(TmpCell->song, X);
        TmpCell->next = P->next;
        P->next = TmpCell;
}

void Delete(ElementType X, List L){
        Position P, TmpCell;

        P = FindPrevious(X, L);

        if(P==NULL || P->next == NULL){ //X가 없는 경우의 FindPrevious 의 p->next가 NULL
                printf("Deletion Failed! %s is not in the list.\n",X);
                return;
        }

        TmpCell = P->next;
        P->next = TmpCell->next;
        free(TmpCell);

        printf("Delete %s successfully!\n", X);
}

void PrintList(List L){

        Position P = L->next;

        if(P == NULL){
                printf("List is empty now!\n");
                return;
        }
        printf("\n");
        printf("[Playlist]\n");
        while(P != NULL){
                printf("%s", P->song);
                if(P->next != NULL){
                        printf(" -> ");
                }
                P = P->next;
        }
        printf("\n");
        printf("\n");
}


void DeleteList(List L){
        Position P, Tmp;
        P=L->next;
        L->next = NULL;
        while(P!=NULL){
                Tmp = P->next;
                free(P);
                P = Tmp;
        }
}

int main(int argc, char *argv[]) {
        if (argc != 2) {
                printf("Error: No input file specified. Please provide the input file via a command-line argument.\n");
                return 1;
        }

        FILE *fp = fopen(argv[1], "r");

        if(fp == NULL){
        printf("Error: No input file specified. Plaese provide the input file via a command-line argument.\n");
        return 1;
        }

        List playlist = MakeEmpty();
        char command;
        char song[256], prev_song[256];
        Position tmp;

        while(fscanf(fp, " %c", &command)  != EOF){
                switch(command){
                        case 'i': //insert
                                fscanf(fp, " %s %s", song, prev_song);
                                tmp = strcmp(prev_song, "s") == 0 ? playlist : Find(prev_song, playlist); //"s" == header
                                if (tmp == NULL){
                                        printf("Insertion (%s) Failed! Cannot find the location to be inserted.\n", song);
                                }
                                else{
                                        Insert(song, playlist, tmp);
                                        printf("Insert %s successfully!\n", song);
                                }
                                break;
                        case 'd': //delete
                                fscanf(fp, " %s", song);
                                Delete(song, playlist);
                                break;
                        case 'p': //print
                                PrintList(playlist);
                                break;
                        case 'f':
                                fscanf(fp, " %s", song);
                                tmp = FindPrevious(song, playlist);
                                if(tmp->next == NULL){
                                        printf("Error: Cannot find %s.\n",song);
                                }
                                else{
                                        if(strcmp(tmp->song, "\0") == 0){
                                                printf("%s is the first song!\n", song);
                                        }
                                        else{
                                                printf("Previous song of %s: %s\n", song, tmp->song);
                                        }

                                }
                                break;
                }
        }

        fclose(fp);
        DeleteList(playlist);
        return 0;
}
