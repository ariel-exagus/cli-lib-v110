#include "cli.h"

int main()
{
    // Registrar comandos
    CLI_RegisterCommand("hello", cmd_hello, "Imprime un mensaje de saludo");
    CLI_RegisterCommand("echo", cmd_echo, "Repite los argumentos proporcionados");

    // Inicializar CLI
    CLI_Init();

    // Bucle principal
    while (true) {
        CLI_Task();
    }

    return 0;
}