#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HeapStruct* Heap;
struct HeapStruct{
    int Capacity;
    int Size;
    int *Element;
};

Heap CreateHeap(int heapSize);
void Insert(Heap heap, int value);
int Find(Heap heap, int value);
void DeleteMax(Heap heap);
void PrintHeap(Heap heap);
void BuildHeap(Heap heap, int n);
void PercDown(Heap heap, int i, int n);
void FreeHeap(Heap heap);

Heap CreateHeap(int heapSize){
    Heap h = (Heap)malloc(sizeof(struct HeapStruct));
    h->Element = (int*)malloc(sizeof(int)*(heapSize+1));
    h->Size = 0;
    h->Capacity = heapSize;
    return h;
}

void PercDown(Heap heap, int i, int n){
    int v = heap->Element[i];
    int child;
    while(i*2 <= n){
        child = i*2;
        if(child < n && heap->Element[child] < heap->Element[child+1]){
            child++;
        }
        if(v >= heap->Element[child]){
            break;
        }
        heap->Element[i] = heap->Element[child];
        i=child;
    }
    heap->Element[i]=v;
}
void BuildHeap(Heap heap, int n){
    for(int i=n/2;i>=1;i--){
        PercDown(heap,i,n);
    }
}

int Find(Heap heap, int value){
    for(int i=1 ; i<=heap->Size; i++){
        if(heap->Element[i]==value){
            return 1;
        }
    }
    return 0;
}

void Insert(Heap heap, int value){
    if(Find(heap, value)){
        printf("%d is already in the heap.\n",value);
        return;
    }
    if(heap->Size >= heap->Capacity){
        printf("Insertion Error : Max Heap is full!\n");
        return;
    }
    int i = ++(heap->Size);
    while(i >1 && heap->Element[i/2]<value){
        heap->Element[i] = heap->Element[i/2];
        i=i/2;
    }
    heap->Element[i]=value;
    printf("Insert %d\n", value);
}
void DeleteMax(Heap heap){
    if(heap->Size==0){
        printf("Deletion Error : Max Heap is empty!\n");
        return;
    }
    int max = heap->Element[1];
    heap->Element[1] = heap->Element[heap->Size--];
    if(heap->Size >0){
        PercDown(heap, 1, heap->Size);
    }
    printf("Max Element %d is deleted.\n",max);
}

void PrintHeap(Heap heap){
    if(heap->Size == 0){
        printf("Print Error : Max Heap is empty!\n");
        return;
    }
    for(int i=1;i<=heap->Size;i++){
        if(i>1){
            printf(" ");
        }
        printf("%d", heap->Element[i]);
    }
    printf("\n");
}
void FreeHeap(Heap heap){
    free(heap->Element);
    free(heap);
}

int main(int argc, char* argv[]) {
    FILE *fi = fopen(argv[1], "r");
    char cmd;
    Heap maxHeap = NULL;
    int heapSize, key;

    while ((cmd = fgetc(fi)) != EOF) {
        switch (cmd) {
            case 'n':
                fscanf(fi, "%d", &heapSize);
                maxHeap = CreateHeap(heapSize);
                break;
            case 'b': {
                if (!maxHeap) {
                    printf("BuildHeap Error : Heap not created. Use 'n x' first.\n");
                    break;
                }
                char buffer[30];
                fgets(buffer, sizeof(buffer), fi);
                char* token = strtok(buffer, " \n");
                int index = 1;
                while (token && index <= maxHeap->Capacity) {
                    int val = atoi(token);
                    maxHeap->Element[index++] = val;
                    token = strtok(NULL, " \n");
                }
                maxHeap->Size = index - 1;
                BuildHeap(maxHeap, maxHeap->Size);
                break;
            }
            case 'i':
                fscanf(fi, "%d", &key);
                Insert(maxHeap, key);
                break;
            case 'd':
                DeleteMax(maxHeap);
                break;
            case 'f':
                fscanf(fi, "%d", &key);
                if (Find(maxHeap, key))
                    printf("%d is in the heap.\n", key);
                else
                    printf("%d is not in the heap.\n", key);
                break;
            case 'p':
                PrintHeap(maxHeap);
                break;
        }
    }
    FreeHeap(maxHeap);
    fclose(fi);
    return 0;
}