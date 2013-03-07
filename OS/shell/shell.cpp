#include "shell.hpp"


shell::shell() {
    run = true;
}

void shell::init() {

	while(run) {

		printPrompt();

		std::string input;
		std::getline(std::cin, input);

		if (input.empty())
			continue;

        execute(input);

	}
}

void shell::execute(std::string input) {

    execute(parseCommand(input));

}

int shell::execute(command cmd) {

    int status = 0;

    if (executeLocal(cmd)) {
        return status;
    }

    int pid = fork();

    if (pid == 0) {

        cmd.args.push_back(0);

        execvp(cmd.args[0], (char * const *) &cmd.args[0]);

        std::cout << "Unknown command " << cmd.args[0] << "was not found, try \"help\"" << '\n';

    }
    else {
        if (cmd.background){

                // If we are at the max of BG jobs AND cannot purge out recently completed ones
                if ( ( jobs.size() >= maxjobs ) && ( !purgeJobs()) ) {
                    purgeJobs();
                    std::cout << "max number of background jobs reached, wait for a process to finish and try again or try \"killall\" or killing a single process" << '\n';
                    return status;
                }

                job thisJob = {cmd, pid};

                jobs.push_back(thisJob);
                std::cout << "nametest: " << jobs.front().cmd.args[0] << '\n';
                listjobs();
                std::cout << "[" << pid << "]+ in background   " << cmd.args[0] << '\n';

                std::cout << "back of jobs " << jobs.back().cmd.args[0] << '\n';
                return status;
        }

        wait(&status);
    }

    return status;
}

shell::command shell::parseCommand(std::string input) {

    command cmd;

    if (input[input.length()-1] == '&') {
        cmd.background = true;
        input = input.substr(0, input.size()-1);
    }
    else
    	cmd.background = false;

	std::stringstream strstr(input);

	// use stream iterators to copy the stream to the vector as whitespace separated strings
	std::istream_iterator<std::string> it(strstr);
	std::istream_iterator<std::string> end;
	std::vector<std::string> tempStringargs(it, end);

    // feed the temporary vector of String type args into a temporary vector of const char * args

    std::vector<const char*> tempConstargs;

    for(int i = 0; i < tempStringargs.size(); i++)
        tempConstargs.push_back(tempStringargs[i].c_str());

    cmd.args = tempConstargs;

    return cmd;
}

void shell::printPrompt() {

	char hostname[128];
	gethostname(hostname, 128);
	std::cout 	<< "\e[0;32m" << getenv("USER") << "@" << hostname
				<< " \e[0;33m" << getenv("PWD") << '\n' << "\e[00m" << "$ ";
}


void shell::cd(command cmd) {
    if(cmd.args[1])
        chdir(cmd.args[1]);

    char pwd[1024];
    getcwd(pwd, sizeof(pwd) - 1);
    setenv("PWD", pwd, true);
}


void shell::clr() {
    system("clear");
}


void shell::dir() {
    system("dir -l");
}


void shell::environ() {

    // Path to the shell
    char buffer[1024];
    ssize_t len = ::readlink("/proc/self/exe", buffer, sizeof(buffer)-1);
    if (len != -1) {
        // truncating the buffer to the actual length needed
        buffer[len] = '\0';
        std::cout << "SHELL = " << std::string(buffer) << '\n';
    }
    else
        std::cout << "Could not resolve path of shell" << '\n';

    // print the other variables too
    std::cout << "USER = " << getenv("USER") << '\n';
    std::cout << "PWD = " << getenv("PWD") << '\n';
    std::cout << "HOME = " << getenv("HOME") << '\n';

}


void shell::echo(command cmd) {

    std::cout << cmd.args[1] << '\n';
}


void shell::help() {

    // string to hold directory where the shell is, the help should be here
    std::string shellDir;

    // Path to the shell
    char buffer[1024];
    ssize_t len = ::readlink("/proc/self", buffer, sizeof(buffer)-1);
    if (len != -1) {
        // truncating the buffer to the actual length needed
        buffer[len] = '\0';
        std::string shellDir = std::string(buffer);
    }

    // Just build a call and make it open the help in vim
    std::string vimHelp = "vim " + shellDir + "help.txt";
    execute(vimHelp);
}


void shell::listjobs() {

    if(jobs.empty()) {
        std::cout << "No current jobs running" << '\n';
        return;
    }

    for (std::list<job>::iterator it=jobs.begin(); it != jobs.end(); ++it) {

        std::cout << "status ";
        std::cout << ( (waitpid(it->pid, 0, WNOHANG) == 0 ) ? "running " : "complete ");
        std::cout << it->pid << " | command: " << *it->cmd.args.front() << '\n';
    }

    if (purgeJobs())
        std::cout << "Completed processes purged" << '\n';
}


void shell::killall() {
    while( !jobs.empty() ) {
        kill(jobs.back().pid, SIGTERM);
        wait(0);
        jobs.pop_back();
    }
}


void shell::exit() {
    killall();
    run = false;

}


void shell::logout() {
    exit();
}


void shell::pause() {
    std::cout << "PAUSE | Hit <ENTER> to resume";
    std::cin.ignore();
}


void shell::quit() {
    exit();
}

bool shell::purgeJobs() {

    bool purged = false;

    std::list<job>::iterator it=jobs.begin();

    while ( it != jobs.end()) {
        if ( !(waitpid(it->pid, 0, WNOHANG) == 0) ) {
            it = jobs.erase(it);
            purged = true;
        }
        else
            ++it;
    }


    return purged;
}

bool shell::executeLocal(command cmd) {

    if ( !std::strcmp(cmd.args[0], "cd") ) {
        cd(cmd);
        return 1;
    }
    else if ( !std::strcmp(cmd.args[0], "clr") ) {
        clr();
        return 1;
    }
    else if ( !std::strcmp(cmd.args[0], "dir") ) {
        dir();
        return 1;
    }
    else if ( !std::strcmp(cmd.args[0], "environ") ) {
        environ();
        return 1;
    }
    else if ( !std::strcmp(cmd.args[0], "echo") ) {
        echo(cmd);
        return 1;
    }
    else if ( !std::strcmp(cmd.args[0], "exit") ) {
        exit();
        return 1;
    }
    else if ( !std::strcmp(cmd.args[0], "help") ) {
        help();
        return 1;
    }
    else if ( !std::strcmp(cmd.args[0], "jobs") ) {
        listjobs();
        return 1;
    }
    else if ( !std::strcmp(cmd.args[0], "killall") ) {
        killall();
        return 1;
    }
    else if ( !std::strcmp(cmd.args[0], "logout") ) {
        logout();
        return 1;
    }
    else if ( !std::strcmp(cmd.args[0], "pause") ) {
        pause();
        return 1;
    }
    else if ( !std::strcmp(cmd.args[0], "quit") ) {
        quit();
        return 1;
    }

    return 0;
}
