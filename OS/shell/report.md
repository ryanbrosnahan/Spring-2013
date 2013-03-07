# OS Project 1 - Shell #

### Ryan Brosnahan rjb39 ###

## Description ##
"Shell" is a simple shell that acts as a command line interpreter interface between Linux and a user making system calls. Shell also supports a number of simple built-in commands listed below. It also has the ability to multiple simultaneous background jobs via forking.

## Build Instructions ##
Navigate to the directory containing the shell files and invoke make with **make**. The program will build an executable in the same directory and launch itself.

## Code Review ##
We examine some of the code base and evaluate the decision process involved in why each design, function, data structure, and algorithm were chosen for the final build.

### Design ###
Because there are relatively few internal functions, and because those internal functions are relatively cohesive, the program was limited to a single * shell * object. It may be neccesary in the future to distribute the internal functions to their own class or namespace.

There exists a function called **executeLocal(command)** that attempts to execute a command using an internal function before resorting to execvp(). In this function is a very large set of if statements to see if the user's input corresponds to an internal command. This is not elegant and should be redesigned in a future iteration.

### Data Structures ###
*Shell* features the following public data structures:  


    struct command {
        bool background;               // If the job is for BG
        std::vector<const char*> args;  // Each of the commands
        std::string name;
    };

    struct job {
        command cmd;
        int pid;
    };

    std::list<job> jobs;

It should be noted that command has a two-phase life-cycle. To understand it we must examine what is happening to each of its members during operation.

 1. A new command is being parsed and prepared for execution, the vector command.args points to the location of a variable that holds the results of a parsing of cin.getline()
 2. command.ackground is set true if the command ended with &
 3. command.name is set to a copy of the target of the pointer of args[0] 
 4. If the job is set for background execution, the command is executed via execvp(), and the pid and command are pushed to jobs as a job struct

It should be noted at this point that when a new background job is called, because command.args always points to the results of a parsing of cin.getline(), after a command is on the jobs list it is futile to access args again as it will be addressing a newer command. This is why the std::string name is used, to secure a copy of the name of the command before command.args changes.

### Function ###
The jobs list does not inherently purge completed jobs as they finish. Instead a special function purgeJobs() purges the list of completed jobs only when it is necessary:  

 - If the jobs vector is at capacity of maxjobs  
 - OR If the user calls the jobs function to list all current background jobs

Additionally, I also made the decision to make the help command open a text file in vim. There are better ways of doing this, such using the proper man document formatting and using the man program instead. This may also entail hardcoding the manual into the source, which is often undesirable.
