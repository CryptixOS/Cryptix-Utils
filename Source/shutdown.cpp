/*
 * Created by vitriol1744 on 21.03.2025.
 * Copyright (c) 2024-2025, Szymon Zemke <Vitriol1744@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <Prism/Core/Core.hpp>
#include <Prism/Core/Error.hpp>
#include <Prism/String/StringView.hpp>
#include <cryptix/reboot.hpp>

using namespace cryptix;
using namespace Prism;

#include <cryptix/syscall.h>
#include <linux/reboot.h>
#include <sys/reboot.h>

ErrorOr<void> NeonMain(const Vector<StringView>& argv,
                       const Vector<StringView>& envp)
{
    IgnoreUnused(argv);
    IgnoreUnused(envp);

    printf("The system will be shutdown...\n");
    reboot(LINUX_REBOOT_CMD_POWER_OFF);

    return {};
}
