#include "shell.hpp"

int main() {
    shell shell;
    shell.init();

    std::cout << "shell: Terminated successfully" << '\n';
    return 0;
}
