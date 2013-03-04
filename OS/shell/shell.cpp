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

void shell::execute(command cmd) {
	//execvp(cmd.args[0].c_str(), cmd.args.size());
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
	std::vector<std::string> args(it, end);
	cmd.args = args;

    return cmd;
}

void shell::printPrompt() {

	char hostname[128];
	gethostname(hostname, 128);
	std::cout 	<< "\e[0;32m" << getenv("USER") << "@" << hostname
				<< " \e[0;33m" << getenv("PWD") << '\n' << "\e[00m" << "$ ";
}

void shell::cd() {

}


void shell::clr() {

}


void shell::dir() {

}


void shell::environ() {

}


void shell::echo() {

}


void shell::exit() {

}


void shell::help() {

}


void shell::jobs() {

}


void shell::killall() {

}


void shell::logout() {

}


void shell::pause() {

}


void shell::quit() {

}

