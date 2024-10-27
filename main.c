#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "patterns.h"
#include "process.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <PATTERN_TYPE> <THINGS>\n", argv[0]);
        return 1;
    }

    int pattern_type = atoi(argv[1]);
    int num_things = atoi(argv[2]);

    if (num_things < 1 || num_things > 256) {
        printf("<THINGS> must be between 1 and 256\n");
        return 1;
    }

    srand(time(NULL));

    if (pattern_type == 1) {
        pattern_one(num_things);

    } else if (pattern_type == 2) {
        pattern_two(num_things);
    } else {
        printf("Invalid <PATTERN_TYPE>\n");
        return 1;
    }


    // using process patterns: 

    // int pattern_type = atoi(argv[1]);
    // int num_things = atoi(argv[2]);

    // if (num_things < 1 || num_things > 256) {
    //     printf("<THINGS> must be between 1 and 256\n");
    //     return 1;
    // }

    // srand(time(NULL));

    // if (pattern_type == 1) {
    //     pattern_one(num_things);

    // } else if (pattern_type == 2) {
    //     pattern_two(num_things);
    // } else {
    //     printf("Invalid\n");
    //     return 1;
    // }

    return 0;
}