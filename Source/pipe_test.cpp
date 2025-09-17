/*
 * Created by v1tr10l7 on 14.09.2025.
 * Copyright (c) 2024-2025, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    int         fds[2];
    char        buf[64];
    const char* msg = "hello from parent\n";

    if (pipe(fds) < 0)
    {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        // Child: read end
        close(fds[1]); // close write end
        int n = read(fds[0], buf, sizeof(buf) - 1);
        if (n < 0)
        {
            perror("read");
            return 1;
        }
        buf[n] = '\0';
        printf("child got: %s", buf);
        close(fds[0]);
    }
    else
    {
        // Parent: write end
        close(fds[0]); // close read end
        write(fds[1], msg, strlen(msg));
        close(fds[1]);
    }

    return 0;
}
