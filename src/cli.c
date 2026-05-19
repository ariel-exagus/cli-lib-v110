/*
 * cli.c
 *
 *  Created on: 5 dec 2024
 *      Author: Ariel
 */


#include "../include/cli.h"
//#include "cli.h"

// Lista de comandos registrados
static CLI_Command commandList[MAX_COMMANDS];
static int commandCount = 0;

// Buffer para entrada
static char inputBuffer[MAX_INPUT_LENGTH];
static int inputIndex = 0;

// Funciones estaticas
static void PrintCommandList(void)
{
    for (int i = 0; i < commandCount; i++) {
        printf("  %s - %s\n", commandList[i].name, commandList[i].description);
    }
}

static void PrintUnknownCommandMsg(void)
{
    printf(UNKNOWN_CMD_MSG);
    PrintCommandList();
    printf(END_CMD_MSG);
}

// Implementación de funciones
void CLI_Init(void) {

    // Registrar comandos
    CLI_RegisterCommand("hello", cmd_hello, "Print a test message");
    CLI_RegisterCommand("echo", cmd_echo, "Repeat the arguments provided");
    // Colocar la lista de comandos propios
    CLI_RegisterCommand("cli_version", cmd_cli_version, "Prints the CLI version");

    printf("\n===== Welcome to CLI v1.1.0 =====\n");
    printf("List of available commands\n");
    PrintCommandList();
    printf("\nWrite a command.\n");
    printf("> ");
}



void CLI_Task(void) {
    int ch;
    while ((ch = getchar()) != EOF) {
        if (ch == '\n' || ch == '\r') {
            // Comando completo recibido
            inputBuffer[inputIndex] = '\0';
            if (inputIndex > 0) {
                // Parsear entrada
                char *argv[MAX_COMMANDS];
                int argc = 0;
                char *token = strtok(inputBuffer, " ");
                while (token != NULL && argc < MAX_COMMANDS) {
                    argv[argc++] = token;
                    token = strtok(NULL, " ");
                }

                if (argc > 0) {
                    bool command_match = false;
                    // Buscar y ejecutar el comando
                    for (int i = 0; i < commandCount; i++) {
                        if (strcmp(argv[0], commandList[i].name) == 0) {
                            commandList[i].function(argc, argv);
                            command_match = true;
                            break;
                        }
                    }
                    if (!command_match)
                        PrintUnknownCommandMsg();
                }
                else {
                    //printf("Comando no reconocido: %s\n", argv[0]);
                    PrintUnknownCommandMsg();
                }
            }
            inputIndex = 0; // Reiniciar buffer
            printf("> ");
        } else if (inputIndex < MAX_INPUT_LENGTH - 1) {
            inputBuffer[inputIndex++] = (char)ch;
        } else {
            printf("\nError: Command to long.\n");
            inputIndex = 0; // Reiniciar buffer
            printf("> ");
        }
    }
}

void CLI_RegisterCommand(const char *name, CommandFunction function, const char *description) {
    if (commandCount < MAX_COMMANDS) {
        commandList[commandCount++] = (CLI_Command){name, function, description};
    } else {
        printf("Error: No more commands can be registered.\n");
    }
}

// Ejemplo de comandos
void cmd_hello(int argc, char *argv[]) {
    printf("Hello World! - test command\n");
}

void cmd_echo(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");
}

// Comandos definidos por el usuario
void cmd_cli_version(int argc, char *argv[])
{
    printf("CLI version: v1.1.0\n");
}
