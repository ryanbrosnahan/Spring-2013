#include "shell.hpp"


shell::shell() {

}

void shell::init() {

	while(1) {

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

    int status;

    if (executeLocal(cmd)) {
        return status;
    }

    pid_t child_pid = fork();

    if (child_pid == 0) {
	    execvp(cmd.args[0], (char * const *) & cmd.args[0]);

        // If the command wasn't found, cout that there was an issue
        std::cout << "Unknown command, try \"help\"" << std::endl;

    }
    else {
        if (cmd.background) {

            jobs.push_back({child_pid, cmd});
            wait(&status);
        }
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

}


void shell::echo(command cmd) {
    std::cout << cmd.args[1] << '\n';
}


void shell::exit() {
    killall();

}


void shell::help() {

}


void shell::listjobs() {

}


void shell::killall() {
    while( !jobs.empty() ) {
        kill(jobs.back().pid, SIGTERM);
        jobs.pop_back();
    }
}


void shell::logout() {

}


void shell::pause() {

}


void shell::quit() {

}
