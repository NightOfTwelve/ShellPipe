#include "ShellPipe.h"
#include <vector>
#include <string.h>
#include <assert.h>

struct ShellPipe::Impl
{
    std::FILE *pipe;
    std::vector<char> output;
    bool valid;
};

ShellPipe::ShellPipe(const char *command, size_t outputCapacity) : pImpl(new Impl)
{
    pImpl->output.reserve(outputCapacity);
    input(command);
}

ShellPipe::~ShellPipe()
{
    delete pImpl->output;
    delete pImpl;
}

bool ShellPipe::input(std::string command)
{
    pImpl->pipe = popen(command.c_str(), "r");

    if (pImpl->pipe)
    {
        pImpl->valid = true;

        char buffer[pImpl->output.size()]; // no clue what this should be optimized to

        while (fgets(buffer, sizeof(buffer), pImpl->pipe))
        {
            for (std::size_t i = 0; i < strlen(buffer); i++)
            {
                pImpl->output.push_back(buffer[i]);
            }
        }

        if (pImpl->output.size() > 1)
        {
            assert(pImpl->output.back() == '\n');
            pImpl->output.pop_back();
        }

        pclose(pImpl->pipe);
        pImpl->pipe = NULL;
    }
    else
    {
        pImpl->valid = false;
    }

    return pImpl->valid;
}

std::string ShellPipe::output() const
{
    return pImpl->output.size() > 0 ? std::string(&(pImpl->output.front()), pImpl->output.size()) : std::string();
}

std::size_t ShellPipe::capacity() const
{
    return pImpl->output.capacity();
}

void ShellPipe::reserve(std::size_t new_cap)
{
    pImpl->output.reserve(new_cap);
}

bool ShellPipe::valid() const
{
    return pImpl->valid;
}
