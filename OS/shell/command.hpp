#ifndef INCLUDED_COMMAND_HPP
#define INCLUDED_COMMAND_HPP

class command {
public:

    /*
     For testing purposes
     */
    command();

    /*
     Navigates to a directory
     */
    void cd();

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
    void jobs();

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