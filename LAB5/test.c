#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50

typedef struct CustomerStruct{
    int ticketNumber;
    char name[NAME_LEN];
} Customer;

typedef struct CircularQueueStruct{
    Customer* queue;
    int front;
    int rear;
    int count;
    int maxSize;
    int nextTicket;
} *CircularQueue;

CircularQueue MakeEmpty(int maxSize){
    CircularQueue q = (CircularQueue)malloc(sizeof(struct CircularQueueStruct));
    q->queue = (Customer*)malloc(sizeof(Customer) * maxSize);

    q->front = 0;
    q->rear = -1;
    q->count = 0;
    q->maxSize = maxSize;
    q->nextTicket = 1;

    return q;
}

// 비어있는지 확인
int IsEmpty(CircularQueue q){
    return q->count == 0;
}

// 가득 찼는지 확인
int IsFull(CircularQueue q){
    return q->count == q->maxSize;
}

// enqueue
void enqueue(CircularQueue q, char* name){
    if(IsFull(q)){
        printf("The waiting queue is full.\n");
        return;
    }

    q->rear = (q->rear + 1) % q->maxSize;

    strcpy(q->queue[q->rear].name, name);
    q->queue[q->rear].ticketNumber = q->nextTicket++;

    q->count++;

    printf("Ticket issued: #[%d] for %s\n",
           q->queue[q->rear].ticketNumber,
           q->queue[q->rear].name);
}

// dequeue
void dequeue(CircularQueue q){
    if(IsEmpty(q)){
        printf("No one is waiting\n");
        return;
    }

    printf("Now Serving: #%d - %s\n",
           q->queue[q->front].ticketNumber,
           q->queue[q->front].name);

    q->front = (q->front + 1) % q->maxSize;
    q->count--;
}

// 출력
void printQueue(CircularQueue q){
    printf("Waiting list:\n");

    int i = q->front;
    for(int cnt = 0; cnt < q->count; cnt++){
        printf("    #%d - %s\n",
               q->queue[i].ticketNumber,
               q->queue[i].name);

        i = (i + 1) % q->maxSize;
    }
}

// 메모리 해제
void freeQueue(CircularQueue q){
    free(q->queue);
    free(q);
}

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Usage: %s input.txt\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if(!file){
        printf("Failed to open file\n");
        return 1;
    }

    char command;
    char name[NAME_LEN];
    int size;
    CircularQueue q = NULL;

    while(fscanf(file, " %c", &command) != EOF){
        switch(command){
            case 'c':
                fscanf(file, "%d", &size);
                q = MakeEmpty(size);
                break;

            case 'e':
                fscanf(file, " %[^\n]", name);
                enqueue(q, name);
                break;

            case 'd':
                dequeue(q);
                break;

            case 'p':
                printQueue(q);
                break;

            default:
                printf("Unknown command!\n");
        }
    }

    fclose(file);
    freeQueue(q);
    return 0;
}