#include <sys/wait.h>
#include <iostream>

#define MAX_ARGS    64
#define MAX_ARG_LEN 16
#define MAX_LINE_LEN    80
#define WHITESPACE  " ,\t\n"

#ifndef INCLUDED_SHELL_HPP
#define INCLUDED_SHELL_HPP

class shell {
private:

public:

    struct command {
        char *name; //name of the command
        int argc; // how many arguments the command has
        char *argv[MAX_ARGS]; //each of the commands
    };

    shell();
    int init();
    int execute(std::string);
    int execute(command);
    command parseCommand(std::string cmd);
    void printPrompt();
};

#endif