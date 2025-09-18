/*
 * Created by v1tr10l7 on 11.09.2025.
 * Copyright (c) 2024-2025, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define STACK_SIZE 1024 * 64 // 64 KB stack per thread

void* thread1(void*)
{
    static struct timespec ts = {5, 0};
    while (1)
    {
        printf("Thread 1: hello from thread 1\n");
        fflush(stdout);
        nanosleep(&ts, NULL);
    }

    return 0;
}

void* thread2(void*)
{
    static struct timespec ts = {5, 0};
    while (1)
    {
        printf("Thread 2: hello from thread 2\n");
        fflush(stdout);
        nanosleep(&ts, NULL);
    }

    return 0;
}

int main()
{
    // Allocate stacks for threads
    puts("allocating stacks\n");
    char* stack1 = reinterpret_cast<char*>(malloc(STACK_SIZE));
    char* stack2 = reinterpret_cast<char*>(malloc(STACK_SIZE));
    if (!stack1 || !stack2)
    {
        perror("malloc");
        exit(1);
    }

    using thread_fn = void* (*)(void*);
    printf("cloning thread1...\n");
    pthread_t tid1;
    if (pthread_create(&tid1, NULL, reinterpret_cast<thread_fn>(thread1), NULL)
        != 0)
    {
        perror("clone thread 1");
        exit(1);
    }
    printf("success1\n");

    printf("cloning thread2...\n");
    pthread_t tid2;
    if (pthread_create(&tid2, NULL, reinterpret_cast<thread_fn>(thread2), NULL)
        != 0)
    {
        perror("clone thread 2");
        exit(1);
    }
    printf("success2\n");
    // Let main thread wait forever, or you can join explicitly:
    [[maybe_unused]] struct timespec ts = {5, 0};
    pthread_join(tid1, NULL);
    // pthread_join(tid2, NULL);
    (void)thread2;
    // while (true) nanosleep(&ts, nullptr);

    return EXIT_SUCCESS;
}
