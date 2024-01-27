#include <stdio.h>

#define NUM_NODES 4

void print(short mat[NUM_NODES][NUM_NODES]);


int main() {
    short adjmat[NUM_NODES][NUM_NODES] = {
        /*0  1  2  3*/
    /*0*/{0, 1, 0, 0},
    /*1*/{0, 0, 1, 0},
    /*2*/{0, 0, 0, 1},
    /*3*/{1, 0, 0, 0}
    };

    print(adjmat);

    return 0;
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