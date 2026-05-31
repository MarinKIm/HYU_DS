#include <stdio.h>
#include <stdlib.h>

typedef struct _Queue{
    int size;
    int *key;
    int front;
    int rear;
    int count;
} Queue;

typedef struct _Graph{
    int size;
    int *vertex;
    int **edge;
} Graph;

Queue *CreateQueue(int X){
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    Q->size = X;
    Q->front = 0;
    Q->rear = -1;
    Q->count = 0;
    Q->key = (int*)malloc(sizeof(int)*X);
    return Q;
}

void Enqueue(Queue *Q, int item){
    Q->rear = (Q->rear + 1)%(Q->size);
    Q->count++;
    Q->key[Q->rear] = item;
}

int Dequeue(Queue *Q){
    int result = Q->key[Q->front];
    Q->count--;
    Q->front = (Q->front + 1)%(Q->size);
    return result;
}

Graph *CreateGraph(int X){
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G->size = X;
    G->vertex = (int*)malloc(sizeof(int)*X);
    G->edge = (int**)malloc(sizeof(int*)*X);
    for(int i = 0; i < X; i++){
        G->edge[i] = (int*)calloc(X, sizeof(int));
    }
    return G;
}

void InsertEdge(Graph *G, int u, int v){
    int ui = -1, vi = -1;
    for(int i = 0; i < G->size; i++){
        if(G->vertex[i] == u) ui = i;
        if(G->vertex[i] == v) vi = i;
    }
    if(ui != -1 && vi != -1)
        G->edge[ui][vi] = 1;
}

void Topsort(Graph *G){
    int n = G->size;
    int *indegree = (int*)calloc(n, sizeof(int)); //calloc은 배열 값을 0으로 초기화.

    for(int j = 0; j < n; j++){
        for(int i = 0; i < n; i++){
            if(G->edge[i][j] == 1)
                indegree[j]++;
        }
    }

    Queue *Q = CreateQueue(n);

    for(int i = 0; i < n; i++){
        if(indegree[i] == 0)
            Enqueue(Q, i);
    }

    int first = 1;
    while(Q->count > 0){
        int idx = Dequeue(Q);
        if(!first) printf(" ");
        printf("%d", G->vertex[idx]);
        first = 0;

        for(int j = 0; j < n; j++){
            if(G->edge[idx][j] == 1){
                indegree[j]--;
                if(indegree[j] == 0)
                    Enqueue(Q, j);
            }
        }
    }
    printf("\n");

    free(indegree);
    free(Q->key);
    free(Q);
}

int main(int argc, char **argv){
    FILE *fi = fopen(argv[1], "r");
    int X, u, v;

    fscanf(fi, "%d", &X);

    Graph *G = CreateGraph(X);

    for(int i = 0; i < X; i++){
        fscanf(fi, "%d", &G->vertex[i]);
    }

    while(fscanf(fi, "%d %d", &u, &v) != EOF){
        InsertEdge(G, u, v);
    }

    printf("Topological Sort: ");
    Topsort(G);
}
