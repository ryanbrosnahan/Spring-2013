#include "shell.hpp"

int main(int argc, char *argv[]) {
    shell* shell;
    shell->init();
    delete shell;
    return 0;
}