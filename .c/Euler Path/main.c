#include <stdio.h>

#define NUM_NODES 4

void print(short adjmat[NUM_NODES][NUM_NODES]);


int main() {
    short adjmat[NUM_NODES][NUM_NODES] = {
        {0, 1, 0, 1},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}
    };

    print(adjmat);

    return 0;
}

void print(short adjmat[NUM_NODES][NUM_NODES]) {
    for (int x = 0; x < NUM_NODES; x++) {
        for (int y = 0; y < NUM_NODES; y++) {
            printf("%d ", adjmat[x][y]);
        }
        printf("\n");
    }
}