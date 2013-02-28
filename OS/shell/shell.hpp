#include <sys/wait.h>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <istream>
#include <iterator>
#include <sstream>

#ifndef INCLUDED_SHELL_HPP
#define INCLUDED_SHELL_HPP

class shell {
private:

public:

    /*
     Data structure for the commands
     */
    struct command {
        std::string name;               // Name of the command
        std::vector<std::string> args;  // Each of the commands
        bool background ;               // If the job is for BG
    };

    /*
     Constructor
     */
    shell();

    /*
     Starts the main loop
     */
    void init();

    /*
     Executes a command. Really, it takes the string of a command
     and has it parsed and passed to the other execute
     */
    void execute(std::string);

    /*
     Executes the command by forking
     */
    void execute(command);

    /*
     Takes the string of the input and parses it into the command
     and its args and puts it into the command struct and returns
     that
     */
    command parseCommand(std::string);

    /*
     Prints the prompt e.g. user@system path:
     */
    void printPrompt();
};

#endif