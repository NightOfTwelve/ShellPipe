#ifndef NETWORKANALYZER_SHELLPIPE_H
#define NETWORKANALYZER_SHELLPIPE_H

#include <string>

class ShellPipe
{
public:
    ShellPipe(const char *command = NULL, std::size_t outputCapacity = 256);
    ~ShellPipe();

    bool input(std::string command); // tries to execute the given command, returning whether output will be valid
    std::string output() const; // returns the output of the most recent command if it went to STDOUT

    std::size_t capacity() const; // gets the capacity of the underlying buffer that receives output from STDOUT
    void reserve(std::size_t new_cap); // sets the capacity of the underlying buffer that receives output from STDOUT

    // if the capacity is too small for the output of a command, the output WILL BE TRUNCATED!

    bool valid() const; // returns whether the most recent command should have produced a valid output

private:
    ShellPipe(const ShellPipe&); //deleted
    ShellPipe& operator=(const ShellPipe&); //deleted
    struct Impl;
    Impl *pImpl;
};

#endif //NETWORKANALYZER_SHELLPIPE_H
