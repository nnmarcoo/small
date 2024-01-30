#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define NUM_NODES 69
#define STACK_SIZE 128
#define NUM_THREADS 4

typedef struct {
    short adjmat[NUM_NODES][NUM_NODES];
    short visited[NUM_NODES][NUM_NODES];
    short n;
    short stack[STACK_SIZE];
    short topIndex;
    short longest;
} ThreadData;

DWORD WINAPI findpathThread(LPVOID lpParam);

void findpath(short adjmat[NUM_NODES][NUM_NODES], short visited[NUM_NODES][NUM_NODES], short n, short stack[], short *top, short *longest);
void printmat(short adjmat[NUM_NODES][NUM_NODES]);
void printstack(short stack[], short top);
short peek(short stack[], short top);
void pop(short *top);
void push(short stack[], short *top, short value);
short compare(short a[NUM_NODES][NUM_NODES], short b[NUM_NODES][NUM_NODES]);
void readin(char *filepath, short adjmat[NUM_NODES][NUM_NODES]);
void printneighbors(short adjmat[NUM_NODES][NUM_NODES], short n);


int main() {
    short adjmat[NUM_NODES][NUM_NODES] = {0};
    short visited[NUM_NODES][NUM_NODES] = {0};
    readin("g_big.txt", adjmat);

    HANDLE threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].n = i;
        threadData[i].topIndex = -1;
        threadData[i].longest = -1;
        memcpy(threadData[i].adjmat, adjmat, sizeof(adjmat));
        memcpy(threadData[i].visited, visited, sizeof(visited));

        threads[i] = CreateThread(NULL, 0, findpathThread, &threadData[i], 0, NULL);

        if (threads[i] == NULL) {
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }

    WaitForMultipleObjects(NUM_THREADS, threads, TRUE, INFINITE);

    for (int i = 0; i < NUM_THREADS; i++) 
        CloseHandle(threads[i]);

    return 0;
}

DWORD WINAPI findpathThread(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;
    findpath(data->adjmat, data->visited, data->n, data->stack, &(data->topIndex), &(data->longest));
    return 0;
}

void findpath(short adjmat[NUM_NODES][NUM_NODES], short visited[NUM_NODES][NUM_NODES], short n, short stack[], short *top, short *longest) {
    push(stack, top, n);
    if (*top > *longest) {
        *longest = *top;
        printf("%d: ", *top);
        printstack(stack, *top);
    }
    
    for (short x = 0; x < NUM_NODES; x++) {
        if (adjmat[n][x] && !visited[n][x] && !visited[x][n]) {
            visited[x][n] = visited[n][x] = 1;
            findpath(adjmat, visited, x, stack, top, longest);
            visited[x][n] = visited[n][x] = 0;
        }
    }
    pop(top);
}

short peek(short stack[], short top) {
    if (top > -1) 
        return stack[top];
    return -1;
}

void readin(char *filepath, short adjmat[NUM_NODES][NUM_NODES]) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char ch;
    char buffer[NUM_NODES];
    short node = 0;
    memset(buffer, 0, sizeof(buffer));

    while ((ch = fgetc(file)) != EOF) {
        if (ch != '\n' && ch != ' ') 
            sprintf(buffer, "%s%c", buffer, ch); 
        else {
            adjmat[node][atoi(buffer)] = 1;
            memset(buffer, 0, sizeof(buffer));
        } 
        if (ch == '\n')
            node++;
    }
    fclose(file);
}

void printmat(short mat[NUM_NODES][NUM_NODES]) {
    printf("   ");
    for (short i = 0; i < NUM_NODES; i++) { 
        if (i < 10) printf(" "); printf("%d ", i); 
    } 
    printf("\n");

    for (short x = 0; x < NUM_NODES; x++) {
        if (x < 10)
            printf(" ");

        printf("%d  ", x);

        for (short y = 0; y < NUM_NODES; y++) {
            printf("%c  ", mat[x][y] ? '0' : '-');
        }
        printf("\n");
    }
    printf("   ");
    for (short i = 0; i < NUM_NODES; i++) { 
        if (i < 10) printf(" "); printf("%d ", i); 
    }
    printf("\n");
}

void printstack(short stack[], short top) {
    for (short i = 0; i <= top; i++)
        printf("%d ", stack[i]);
    printf("\n");
}

void pop(short *top) {
    if (*top > -1) 
        (*top)--; 
}

void push(short stack[], short *top, short value) {
    if (*top < STACK_SIZE - 1) 
        stack[++(*top)] = value;
}

void printneighbors(short adjmat[NUM_NODES][NUM_NODES], short n) {
    for (short x = 0; x < NUM_NODES; x++)
        if (adjmat[n][x])
            printf("%d ", x);
    printf("\n");
}

short compare(short a[NUM_NODES][NUM_NODES], short b[NUM_NODES][NUM_NODES]) {
    for (short x = 0; x < NUM_NODES; x++) {
        for (short y = 0; y < NUM_NODES; y++) {
            if (a[x][y] != b[x][y])
                return 0;
        }
    }
    return 1;
}
