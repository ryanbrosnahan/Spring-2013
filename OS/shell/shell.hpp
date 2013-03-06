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
#include <cstring>
#include <stdlib.h>

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
        std::vector<const char*> args;  // Each of the commands
        bool background ;               // If the job is for BG
    };

    struct job {
        int pid;
        command cmd;
    };

    std::vector<job> jobs;

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
    int execute(command);

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

    /*

     */
    bool executeLocal(command);

    /*
     Navigates to a directory
     */
    void cd(command);

    /*
     Clears the screen
     */
    void clr();

    /*
     Lists the items in the current directory
     */
    void dir();

    /*
     Lists all environment strings
    */
    void environ();

    /*
     Displays a comment on the screen. Invoked using
     echo comment
    */
    void echo();

    /*
     Quits the shell after closing all background processes
    */
    void exit();

    /*
     Displays the manual
    */
    void help();

    /*
     Lists all background processes
    */
    void listjobs();

    /*
     Kills all background processes
    */
    void killall();

    /*
     Same as exit
    */
    void logout();

    /*
     Pauses operation of the shell until <ENTER> key
    */
    void pause();

    /*
     Same as exit
    */
    void quit();

};

#endif
