#ifndef INCLUDED_COMMAND_HPP
#define INCLUDED_COMMAND_HPP

class command {
public:
    command();
    int cd();
    int clr();
    int dir();
    int environ();
    int echo();
    int exit();
    int help();
    int jobs();
    int killall();
    int logout();
    int pause();
    int quit();
};

#endif