#include "patterns.h"


void sleep_random(int num) {
    int sleep_time = (rand() % 8) + 1;
    printf("Process %d (pid %d) beginning\n", num, getpid());
    printf("Process %d (pid %d): sleeping for %d seconds...\n", num, getpid(),
           sleep_time);
    sleep(sleep_time);
}

void pattern_one(int things) {
    printf("Pattern 1: creating %d processes\n", things);

    pid_t pid = fork();
    srand(time(NULL));

    for (int ix = 0; ix < things; ix++) {
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            sleep_random(ix);
            printf("pattern one:\n");
            printf("Process %d (pid %d): exiting\n", ix, getpid());
            exit(0);
        } else {
            printf("Parent: created child %d (pid %d)\n", ix, pid);
        }
    }
    for (int ix = 0; ix < things; ix++) {
        wait(NULL);
    }
    printf("** Pattern 1: All children have exited\n\n");
}

void pattern_two(int things2) {
    printf("**Pattern 2: creating %d processes\n", things2);
    pid_t pid = fork();

    if (things2 > 0) {
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            fprintf(stderr, "Child %d (pid %d): starting\n", things2, getpid());

            if (things2 > 1) {
                fprintf(
                    stderr, "Child %d (pid %d), sleeping 9 seconds after creating "
                    "child %d\n",
                    things2, getpid(), things2 - 1);
                sleep(9);
                pattern_two(things2 - 1);
            } else {
                fprintf(
                    stderr, "Child %d (pid %d) [no children created] sleeping 9 "
                    "seconds\n",
                    things2, getpid());
                sleep(9);
            }

            fprintf(stderr, "Child %d (pid %d) exiting.\n", things2, getpid());
            exit(0);
        } else {
            wait(NULL);
            fprintf(stderr, "Parent: child %d (pid %d) has exited\n", things2, pid);
        }
    } else {
        printf("** Pattern 2: All children have exited\n");
    }
}