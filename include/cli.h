/*
 * cli.h
 *
 *  Created on: 5 dec 2024
 *      Author: Ariel
 */

#ifndef INC_CLI_H_
#define INC_CLI_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COMMANDS 10
#define MAX_INPUT_LENGTH 64
#define NEWLINE "\r\n"

// Define messages
#define UNKNOWN_CMD_MSG "--------------------------------------------\n"\
                        "Unknown command. List of available commands:\n"

#define END_CMD_MSG     "--------------------------------------------\n"

// Tipo de función para comandos
typedef void (*CommandFunction)(int argc, char *argv[]);

// Estructura de un comando
typedef struct {
    const char *name;
    CommandFunction function;
    const char *description;
} CLI_Command;


// Prototipos
void CLI_Init(void);
void CLI_Task(void);
void CLI_RegisterCommand(const char *name, CommandFunction function, const char *description);

//comandos
void cmd_hello(int argc, char *argv[]);
void cmd_echo(int argc, char *argv[]);
void cmd_cli_version(int argc, char *argv[]);

#endif /* INC_CLI_H_ */