#include <stdio.h>
#include <stdbool.h>

#define NUM_NODES 6
#define MAX_NODES 15

void dfs(short adjmat[NUM_NODES][NUM_NODES], int node, bool visited[NUM_NODES]);
void print(short adjmat[NUM_NODES][NUM_NODES]);


int main() {
    short adjmat[NUM_NODES][NUM_NODES] = {
        /*0  1  2  3  4  5*/
    /*0*/{0, 1, 1, 0, 1, 1},
    /*1*/{1, 0, 1, 0, 1, 1},
    /*2*/{1, 1, 0, 1, 0, 1},
    /*3*/{0, 0, 1, 0, 1, 0},
    /*4*/{1, 1, 0, 1, 0, 1},
    /*5*/{1, 1, 1, 0, 1, 0}};

    bool visited[NUM_NODES] = {false};

    dfs(adjmat, 0, visited);

    return 0;
}

void dfs(short adjmat[NUM_NODES][NUM_NODES], int node, bool visited[NUM_NODES]) {
    printf("%d ", node);

    visited[node] = true;

    for (int i = 0; i < NUM_NODES; i++) {
        if (adjmat[node][i] == 1 && !visited[i]) {
            dfs(adjmat, i, visited);
        }
    }
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
