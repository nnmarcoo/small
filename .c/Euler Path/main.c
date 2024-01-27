#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// TODO: Take arguments like the adjmat?

#define NUM_NODES 6
#define MAX_NODES 15
#define MAX_EDGES 125

void dfs(short adjmat[NUM_NODES][NUM_NODES], short node, short visited[NUM_NODES][NUM_NODES]);
void print(short adjmat[NUM_NODES][NUM_NODES]);
short compare(short a[NUM_NODES][NUM_NODES], short b[NUM_NODES][NUM_NODES]);
void readin(char *filepath, short adjmat[NUM_NODES][NUM_NODES]);


int main() {
    short adjmat[NUM_NODES][NUM_NODES] = {0};
    short visited[NUM_NODES][NUM_NODES] = {0};

    readin("g_test.txt", adjmat);

    print(adjmat);

    return 0;
}

void dfs(short adjmat[NUM_NODES][NUM_NODES], short n, short visited[NUM_NODES][NUM_NODES]) {
    printf("%d ", n+1);

    for (int x = 0; x < NUM_NODES; x++) {
        if (adjmat[n][x] && !(visited[n][x] + visited[x][n])) {
            visited[n][x] = 1;
            visited[x][n] = 1;
            dfs(adjmat, x, visited);
        }
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
    for (int i = 0; i < NUM_NODES; i++) { printf("%d ", i); } 
    printf("\n   ");
    for (int i = 0; i < NUM_NODES*2; i++) { printf("-"); } 
    printf("\n");

    for (int x = 0; x < NUM_NODES; x++) {
        printf("%d | ", x);
        for (int y = 0; y < NUM_NODES; y++) {
            printf("%d ", mat[x][y]);
        }
        printf("\n");
    }
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
