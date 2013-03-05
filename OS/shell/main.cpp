#include "shell.hpp"

int main(int argc, char *argv[]) {
    shell* shell;
    shell->init();
    delete shell;

    std::cout << "shell: Terminating successfully" << std::endl;
    return 0;
}
