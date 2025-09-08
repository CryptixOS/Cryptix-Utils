/*
 * Created by v1tr10l7 on 10.08.2025.
 * Copyright (c) 2024-2025, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <linux/netlink.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include <Prism/Containers/Vector.hpp>
#include <Prism/Memory/Memory.hpp>
#include <Prism/String/StringView.hpp>
using namespace Prism;

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    printf("udev: creating a netlink socket...\n");
    int fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_KOBJECT_UEVENT);

    if (fd < 0)
    {
        perror("udev: failed to create a netlink socket, aborting...");
        exit(1);
    }

    printf("udev: successfully created a netlink socket\n");

    sockaddr_nl srcAddress;
    Memory::Fill(&srcAddress, 0, sizeof(srcAddress));
    srcAddress.nl_family = AF_NETLINK;
    srcAddress.nl_pid    = getpid();
    srcAddress.nl_groups = 1;

    if (bind(fd, reinterpret_cast<sockaddr*>(&srcAddress), sizeof(srcAddress))
        < 0)
    {
        perror("udev: failed to bind to the netlink socket, aborting...");
        close(fd);
        exit(1);
    }

    constexpr usize MAX_PAYLOAD_SIZE = 1024;
    Vector<char>      buffer;
    buffer.Resize(MAX_PAYLOAD_SIZE);

    printf("udev: starting uevent loop...\n");
    for (;;)
    {
        isize len = recv(fd, buffer.Raw(), MAX_PAYLOAD_SIZE - 1, 0);
        if (len < 0)
        {
            perror("udev: recv failed\n");
            break;
        }
        buffer[len]       = '\0';

        StringView uevent = buffer.Raw();
        for (isize offset = 0; offset < len;
             offset += static_cast<isize>(uevent.Size()) + 1,
                   uevent = &buffer[offset])
            printf("udev: %s\n", uevent.Raw());
    }

    printf("udev: exiting...");
    close(fd);
    return 0;
}
