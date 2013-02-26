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
        char *name;
        int argc;
        char *argv[MAX_ARGS];
    };

    shell();
    void init();
    int parseCommand(char *cLine, struct command_t *cmd);
    void printPrompt();
    void readCommand(char *buffer);
};

#endif