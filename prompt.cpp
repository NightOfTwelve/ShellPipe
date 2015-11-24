#include <iostream>
#include "ShellPipe.h"

int main()
{
    ShellPipe shell;

    std::string input;

    do
    {
        shell.input(input);
        std::cout << shell.output() << std::endl;
        std::cout << "Input> ";
    } while (std::getline(std::cin, input));
}