#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_NODES 69
#define STACK_SIZE 110
#define MAX_REPEATS 0

void findpath(short adjmat[NUM_NODES][NUM_NODES], short visited[NUM_NODES][NUM_NODES], short n, short stack[], short *top, short *longest, short repeats, short previous, short pruned[]);
short compare(short a[NUM_NODES][NUM_NODES], short b[NUM_NODES][NUM_NODES]);
void printneighbors(short adjmat[NUM_NODES][NUM_NODES], short n);
short countneighbors(short adjmat[NUM_NODES][NUM_NODES], short n);
void readin(char *filepath, short adjmat[NUM_NODES][NUM_NODES]);
void printmat(short adjmat[NUM_NODES][NUM_NODES]);
void push(short stack[], short *top, short value);
void printstack(short stack[], short top);
short peek(short stack[], short top);
void pop(short *top);


int main() {
    short adjmat[NUM_NODES][NUM_NODES] = {0};
    short visited[NUM_NODES][NUM_NODES] = {0};
    short pruned[NUM_NODES] = {0};

    readin("g_big.txt", adjmat);

    short stack[STACK_SIZE];
    short topIndex = -1;
    short longest = -1;
    short startnode = 1;
    
    findpath(adjmat, visited, startnode, stack, &topIndex, &longest, MAX_REPEATS, startnode, pruned);

    return 0;
}

void findpath(short adjmat[NUM_NODES][NUM_NODES], short visited[NUM_NODES][NUM_NODES], short n, short stack[], short *top, short *longest, short repeats,  short previous, short pruned[]) {
    push(stack, top, n);
    if (*top > *longest) {
        *longest = *top;
        printf("%d: ", *top);
        printstack(stack, *top);
    }
    for (short x = 0; x < NUM_NODES; x++) {
        if (adjmat[n][x] && (!(visited[n][x] && visited[x][n]) || repeats > 0 && countneighbors(adjmat, n) % 2 != 0) && x != previous && pruned[x]) {
            if (visited[n][x] && visited[x][n]) repeats--;
            visited[x][n] = visited[n][x] = 1;
            findpath(adjmat, visited, x, stack, top, longest, repeats, n, pruned);
            visited[x][n] = visited[n][x] = 0;
        }
    }
    pruned[n] = 1;
    repeats = MAX_REPEATS;
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

short countneighbors(short adjmat[NUM_NODES][NUM_NODES], short n) {
    int count = 0;
    for (short x = 0; x < NUM_NODES; x++)
        if (adjmat[n][x])
            count++;
    return count;
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
