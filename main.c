#include "cli.h"

int main()
{

    // Inicializar CLI
    CLI_Init();

    // Bucle principal
    while (true) {
        CLI_Task();
    }

    return 0;
}