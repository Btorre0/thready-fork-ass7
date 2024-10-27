#ifndef PATTERNS_H
#define PATTERNS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void *threading(void *arg);
void sleep_random(int num);
void pattern_one(int things);
void pattern_two(int things2);

#endif