#include "patterns.h"

void sleep_random(int num) {
    int sleep_t = ((rand() % 8) + 1);
    printf("Thread %d (pid %d, tid %lu) beginning\n", num, getpid(),
           (unsigned long)pthread_self());
    printf("Thread %d (pid %d, tid %lu), seconds %d sleeping\n", num, getpid(),
           (unsigned long)pthread_self(), sleep_t);
    sleep(sleep_t);
}

void *threading_one(void *arg) {
    int num = *((int *)arg);
    printf("thread in child: %d\n", getpid());
    sleep_random(num);
    printf("pattern one: Thread: %d (pid %d, tid %lu): exiting\n", num,
           getpid(), (unsigned long)pthread_self());
    return NULL;
}

void pattern_one(int things) {
    printf("pattern 1 creating %d Thread\n", things);
    pthread_t thread[things];
    int thread_num[things];

    for (int ix = 0; ix < things; ix++) {
        thread_num[ix] = ix + 1;
        if (pthread_create(&thread[ix], NULL, threading_one, &thread_num[ix]) !=
            0) {
            perror("pthread_create failed");
            pthread_exit(NULL);
        }
    }
    for (int ix = 0; ix < things; ix++) {
        pthread_join(thread[ix], NULL);
    }

    printf("** Pattern 1: all children have exited\n\n");
}

void *threading_two(void *arg) {
    int num = *((int *)arg);
    int sleep_t = ((rand() % 8) + 1);

    // printf("thread in child: %d\n", getpid());
    printf("Thread %d (pid %d, tid %lu) beginning\n", num, getpid(),
           (unsigned long)pthread_self());
    printf("Thread %d (pid %d, tid %lu), seconds %d sleeping\n", num, getpid(),
           (unsigned long)pthread_self(), sleep_t);

    if (num > 1) {
        pthread_t child_thread;
        int *child_num = malloc(sizeof(int));
        if (child_num == NULL) {
            perror("malloc failed");
            pthread_exit(NULL);
        }
        *child_num = num - 1;
        fprintf(stderr, "Child %d (pid %d, tid %lu) creating child %d\n", num,
                getpid(), (unsigned long)pthread_self(), *child_num);
        if (pthread_create(&child_thread, NULL, threading_two, child_num) !=
            0) {
            perror("pthread_create failed");
            free(child_num);
            pthread_exit(NULL);
        }
        if (pthread_join(child_thread, NULL) != 0) {
            perror("pthread_join failed");
            free(child_num);
            pthread_exit(NULL);
        }
        free(child_num);
    } else {
        fprintf(stderr,
                "Child %d (pid %d, tid %lu) [no children created] sleeping %d "
                "seconds\n",
                num, getpid(), (unsigned long)pthread_self(), sleep_t);
        sleep(sleep_t);
    }
    // sleep_random(num);
    printf("pattern two: Thread: %d (pid %d, tid %lu): exiting\n", num,
           getpid(), (unsigned long)pthread_self());
    return NULL;
}

void pattern_two(int things2) {
    printf("**Pattern 2: creating %d Thread\n", things2);

    pthread_t thread;
    int *thread_num = malloc(sizeof(int));

    if (thread_num == NULL) {
        perror("malloc failed");
        pthread_exit(NULL);
    }
    *thread_num = things2;

    if (things2 > 0) {
        // thread_num = 1;
        if (pthread_create(&thread, NULL, threading_two, thread_num) != 0) {
            perror("pthread_create failed");
            pthread_exit(NULL);
        }
        pthread_join(thread, NULL);
        free(thread_num);
    }
    printf("** Pattern 2: All children have exited\n");
}