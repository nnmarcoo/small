#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// TODO: Take arguments like the adjmat?

#define NUM_NODES 69
#define MAX_EDGES 10

void dfs(short adjmat[NUM_NODES][NUM_NODES], short visited[NUM_NODES][NUM_NODES], short n, short d);
void print(short adjmat[NUM_NODES][NUM_NODES]);
short compare(short a[NUM_NODES][NUM_NODES], short b[NUM_NODES][NUM_NODES]);
void readin(char *filepath, short adjmat[NUM_NODES][NUM_NODES]);
void printneighbors(short adjmat[NUM_NODES][NUM_NODES], short n);


int main() {
    short adjmat[NUM_NODES][NUM_NODES] = {0};
    short visited[NUM_NODES][NUM_NODES] = {0};

    readin("g_big.txt", adjmat);

    dfs(adjmat, visited, 1, MAX_EDGES);



    return 0;
}

void dfs(short adjmat[NUM_NODES][NUM_NODES], short visited[NUM_NODES][NUM_NODES], short n, short d) {
    printf("%d ", n);
    
    for (int x = 0; x < NUM_NODES; x++) {
        if (adjmat[n][x] && !visited[n][x]) {
            d--; if (!d) break;
            
    
            visited[x][n], visited[n][x] = 1;
            dfs(adjmat, visited, x, d);
            printf("\n");
        }
        d = MAX_EDGES;
    }
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

void print(short mat[NUM_NODES][NUM_NODES]) {
    printf("    ");
    for (int i = 0; i < NUM_NODES; i++) { if (i < 10) printf(" "); printf("%d ", i); } 
    printf("\n   ");
    for (int i = 0; i < NUM_NODES*2; i++) { printf("-"); } 
    printf("\n");

    for (int x = 0; x < NUM_NODES; x++) {
        if (x < 10) printf(" ");
        printf("%d | ", x);
        for (int y = 0; y < NUM_NODES; y++) {
            printf("%d  ", mat[x][y]);
        }
        printf("\n");
    }
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
