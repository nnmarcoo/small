#include <stdio.h>

#define NUM_NODES 4

void printAdjacencyMatrix(short adjMatrix[NUM_NODES][NUM_NODES]) {
    for (int i = 0; i < NUM_NODES; ++i) {
        for (int j = 0; j < NUM_NODES; ++j) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    short adjacencyMatrix[NUM_NODES][NUM_NODES] = {
        {0, 1, 0, 1},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}
    };

    printAdjacencyMatrix(adjacencyMatrix);

    return 0;
}
