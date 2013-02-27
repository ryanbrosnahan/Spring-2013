#include "shell.hpp"
#include "command.hpp"

#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <string>


shell::shell() {

}

int shell::init() {

	while(1) {

		printPrompt();

		std::string input;
		std::getline(std::cin, input);
		
		if (input.empty())
			continue;

	}
}

shell::command shell::parseCommand(std::string input) {

   command cmd;
   return cmd;
}

int execute(std::string input) {
	command cmd;
	cmd = shell::parseCommand("test");

}

int execute(command cmd) {

}

void shell::printPrompt() {

	char hostname[128];
	gethostname(hostname, 128);
	std::cout 	<< getenv("USER") << "@" << hostname 
				<< " " << getenv("HOME") << ": ";
}

