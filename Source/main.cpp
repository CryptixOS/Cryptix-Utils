/*
 * Created by v1tr10l7 on 02.09.2025.
 * Copyright (c) 2024-2025, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <cstdlib>

#include <Prism/Debug/Log.hpp>

using namespace Prism;

int NeonMain(const Vector<StringView>&, const Vector<StringView>&)
{
    Log::Logf(LogLevel::eDebug, "Hello, World!");

    return EXIT_SUCCESS;
}
