#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 1024
#define CAPACITY 512
#define LANE_SIZE 64
#define NUM_LANES (BLOCK_SIZE / LANE_SIZE)

int main() {
    uint64_t state[NUM_LANES] = {0};
    int num_zero_lanes = CAPACITY / LANE_SIZE;
int block;
for (block = 0; block < 1000; block++) {
        int i;
		for (i = 0; i < NUM_LANES; i++) {
            state[i] ^= 1;
        }
        int new_num_zero_lanes = 0;
		for (i = 0; i < NUM_LANES; i++) {
            if (state[i] == 0 && i < CAPACITY/ LANE_SIZE)
                new_num_zero_lanes++;
        }
        num_zero_lanes = new_num_zero_lanes;

        printf("Block %d: %d zero lanes\n", block, num_zero_lanes);
        if (num_zero_lanes == 0)
            break;
    }

    return 0;
}

