/*
 * Created by v1tr10l7 on 23.06.2025.
 * Copyright (c) 2024-2025, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#define PRISM_LOG_ENABLE true

#include <Prism/Containers/Array.hpp>
#include <Prism/Containers/Vector.hpp>
#include <Prism/Core/Error.hpp>
#include <Prism/Debug/Log.hpp>
#include <Prism/String/String.hpp>
#include <Prism/String/StringUtils.hpp>
#include <Prism/Utility/Optional.hpp>
#include <Prism/Utility/Path.hpp>

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace Prism;
using namespace Prism::Literals;
using namespace Prism::StringUtils;

void print(StringView str)
{
    for (usize i = 0; i < str.Size(); i++) putchar(str[i]);
}

ErrorOr<void> NeonMain(const Vector<StringView>& argv,
                       const Vector<StringView>& envp)
{
    if (argv.Size() <= 1) return Error(errno);

    StringView username = argv[1];
    FILE*      passwd   = fopen("/etc/passwd", "r");
    fseek(passwd, 0, SEEK_END);
    usize size = ftell(passwd);
    fseek(passwd, 0, SEEK_SET);

    String file = ""_s;
    file.Resize(size + 1);

    fread(file.Raw(), size, 1, passwd);
    file[size] = 0;
    print(file);

    Optional<uid_t> uid       = NullOpt;
    Optional<gid_t> gid       = NullOpt;
    String          shellPath = ""_s;

    usize           start     = 0;
    auto            end       = file.FindFirstOf("\n");
    while ((end = file.View().FindFirstOf("\n", start)) < file.Size()
           && start < file.Size())
    {
        usize      length = end - start;
        StringView line   = file.View().Substr(start, length);
        start             = end + 1;

        while (start < file.Size() && !IsAlphanumeric(file[start])) ++start;

        if (length == 0) continue;
        if (end == String::NPos) end = file.Size();

        auto segments = line.Split(':');
        if (segments[0] == username)
        {
            uid            = ToNumber<uid_t>(segments[2]);
            gid            = ToNumber<gid_t>(segments[3]);

            auto lastColon = line.FindLastOf(":");
            shellPath      = line.Substr(lastColon + 1);
            break;
        }
    }

    if (!uid) return Error(errno);

    printf("found user: %s with uid %u, and gid: %u", username.Raw(),
           uid.Value(), gid.Value());

    setresuid(uid.Value(), uid.Value(), uid.Value());
    setresgid(gid.Value(), gid.Value(), gid.Value());
    print("\n");

    uid_t uidCurrent = getuid();
    gid_t gidCurrent = getgid();

    print("uid => ");
    print(ToString(uidCurrent));
    print("\n");

    print("gid => ");
    print(ToString(gidCurrent));
    print("\n");

    Array<const char*, 3> argvArr = {
        shellPath.Raw(),
        "-i",
        0,
    };

    print("\n");
    print(shellPath);
    print("\n");

    Vector<const char*> envs;
    for (const auto& env : envp) envs.PushBack(env.Raw());

    int pid = fork();
    if (pid == -1)
    {
        perror("su: fork failed");
        return Error(errno);
    }
    else if (pid == 0)
        execve(shellPath.Raw(), const_cast<char* const*>(argvArr.Raw()),
               const_cast<char* const*>(envs.Raw()));

    int status;

    if (waitpid(-1, &status, 0) == pid)
    {
        bool exited = WIFEXITED(status);
        if (exited)
            printf("su: child % died with exit code %d\n", pid,
                   WEXITSTATUS(status));
    }
    return {};
}
