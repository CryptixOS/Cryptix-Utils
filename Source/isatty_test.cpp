/*
 * Created by v1tr10l7 on 14.09.2025.
 * Copyright (c) 2024-2025, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    const char* path = "/dev/console";
    int         fd   = open(path, O_RDONLY, 0);
    printf("isatty(%s): %d\n", path, isatty(fd));

    return 0;
}
