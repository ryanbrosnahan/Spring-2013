#include "shell.hpp"
#include "command.hpp"

#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <string>


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

    command cmd = parseCommand(input);

}

void shell::execute(command cmd) {

}

shell::command shell::parseCommand(std::string input) {

    command cmd;

    if (input.back() == '&') {
        return cmd;
    }

    std::array<int, 10> test;

    return cmd;
}

void shell::printPrompt() {

	char hostname[128];
	gethostname(hostname, 128);
	std::cout 	<< "\e[0;32m" << getenv("USER") << "@" << hostname
				<< " \e[0;33m" << getenv("PWD") << '\n' << "\e[00m" << "$ ";
}

