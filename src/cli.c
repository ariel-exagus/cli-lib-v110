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

// Implementación de funciones
void CLI_Init(void) {
    printf("\n=== Bienvenido al CLI ===\n");
    printf("Comandos disponibles:\n");
    for (int i = 0; i < commandCount; i++) {
        printf("  %s - %s\n", commandList[i].name, commandList[i].description);
    }
    printf("\nEscribe un comando seguido de sus argumentos.\n");
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
                    // Buscar y ejecutar el comando
                    for (int i = 0; i < commandCount; i++) {
                        if (strcmp(argv[0], commandList[i].name) == 0) {
                            commandList[i].function(argc, argv);
                            break;
                        }
                    }
                }
                else {
                    printf("Comando no reconocido: %s\n", argv[0]);
                }
            }
            inputIndex = 0; // Reiniciar buffer
            printf("> ");
        } else if (inputIndex < MAX_INPUT_LENGTH - 1) {
            inputBuffer[inputIndex++] = (char)ch;
        } else {
            printf("\nError: Comando demasiado largo.\n");
            inputIndex = 0; // Reiniciar buffer
            printf("> ");
        }
    }
}

void CLI_RegisterCommand(const char *name, CommandFunction function, const char *description) {
    if (commandCount < MAX_COMMANDS) {
        commandList[commandCount++] = (CLI_Command){name, function, description};
    } else {
        printf("Error: No se pueden registrar más comandos.\n");
    }
}

// Ejemplo de comandos
void cmd_hello(int argc, char *argv[]) {
    printf("Hola, mundo!\n");
}

void cmd_echo(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");
}
