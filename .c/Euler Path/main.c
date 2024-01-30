#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// TODO: Take arguments like the adjmat?

#define NUM_NODES 6
#define STACK_SIZE 150

void findpath(short adjmat[NUM_NODES][NUM_NODES], short visited[NUM_NODES][NUM_NODES], short n, int stack[], int *top);
void printmat(short adjmat[NUM_NODES][NUM_NODES]);
void printstack(int stack[], int top);
int peek(int stack[], int top);
void pop(int *top);
void push(int stack[], int *top, int value);
short compare(short a[NUM_NODES][NUM_NODES], short b[NUM_NODES][NUM_NODES]);
void readin(char *filepath, short adjmat[NUM_NODES][NUM_NODES]);
void printneighbors(short adjmat[NUM_NODES][NUM_NODES], short n);


int main() {
    short adjmat[NUM_NODES][NUM_NODES] = {0};
    short visited[NUM_NODES][NUM_NODES] = {0};

    readin("g_test.txt", adjmat);

    int stack[STACK_SIZE];
    int topIndex = -1;
    
    findpath(adjmat, visited, 1, stack, &topIndex);

    return 0;
}

void findpath(short adjmat[NUM_NODES][NUM_NODES], short visited[NUM_NODES][NUM_NODES], short n, int stack[], int *top) {
    push(stack, top, n);
    printstack(stack, *top);
    
    for (int x = 0; x < NUM_NODES; x++) {
        if (adjmat[n][x] && !visited[n][x] && !visited[x][n]) {
            visited[x][n] = visited[n][x] = 1;
            findpath(adjmat, visited, x, stack, top);
            visited[x][n] = visited[n][x] = 0;
        }
    }
    pop(top);
}

int peek(int stack[], int top) {
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
    for (int i = 0; i < NUM_NODES; i++) { 
        if (i < 10) printf(" "); printf("%d ", i); 
    } 
    printf("\n");

    for (int x = 0; x < NUM_NODES; x++) {
        if (x < 10)
            printf(" ");

        printf("%d  ", x);

        for (int y = 0; y < NUM_NODES; y++) {
            printf("%c  ", mat[x][y] ? '0' : '-');
        }
        printf("\n");
    }
    printf("   ");
    for (int i = 0; i < NUM_NODES; i++) { 
        if (i < 10) printf(" "); printf("%d ", i); 
    }
    printf("\n");
}

void printstack(int stack[], int top) {
    for (int i = 0; i <= top; i++) 
        printf("%d ", stack[i]);
    printf("\n");
}

void pop(int *top) {
    if (*top > -1) 
        (*top)--; 
}

void push(int stack[], int *top, int value) {
    if (*top < STACK_SIZE - 1) 
        stack[++(*top)] = value;
}

void printneighbors(short adjmat[NUM_NODES][NUM_NODES], short n) {
    for (int x = 0; x < NUM_NODES; x++)
        if (adjmat[n][x])
            printf("%d ", x);
    printf("\n");
}

short compare(short a[NUM_NODES][NUM_NODES], short b[NUM_NODES][NUM_NODES]) {
    for (int x = 0; x < NUM_NODES; x++) {
        for (int y = 0; y < NUM_NODES; y++) {
            if (a[x][y] != b[x][y])
                return 0;
        }
    }
    return 1;
}
