#include "shell.hpp"

int main(int argc, char *argv[]) {
    shell* shell;
    shell->init();
    delete shell;

    printf("\n\n shell: Terminating successfully\n");
    return 0;
}