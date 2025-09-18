/*
 * Created by vitriol1744 on 19.02.2025.
 * Copyright (c) 2024-2025, Szymon Zemke <Vitriol1744@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <Prism/Core/Core.hpp>
#include <Prism/Core/Error.hpp>
#include <Prism/String/StringView.hpp>

using namespace Prism;

#include <cryptix/syscall.h>
#include <linux/reboot.h>
#include <sys/reboot.h>

ErrorOr<void> NeonMain(const Vector<StringView>& argv,
                       const Vector<StringView>& envp)
{
    IgnoreUnused(argv);
    IgnoreUnused(envp);
    printf("The system will reboot...\n");
    reboot(LINUX_REBOOT_CMD_RESTART);

    return Error(errno);
}
