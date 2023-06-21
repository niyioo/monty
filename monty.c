#include "monty.h"
#include <stdio.h>

instruction_t instruction_s[] = {
	{"push", push},
	{"pall", pall},
	{"pint", pint},
	{"pop", pop},
	{"swap", swap},
	{"add", add},
	{"nop", nop},
	{NULL, NULL}
};

/**
 * read_bytecodes - Read Monty bytecodes from a file
 * @file: Pointer to the file containing Monty bytecodes
 *
 * Return: An array of strings containing the bytecodes
 */

char **read_bytecodes(FILE *file)
{
	char **bytecodes = NULL;
	char *line = NULL;
	size_t len = 0;
	size_t bytecodes_count = 0;
	size_t bytecodes_size = 10;
	int ch;
	size_t line_length = 0;

	bytecodes = malloc(bytecodes_size * sizeof(char *));
	if (bytecodes == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	line = malloc(128 * sizeof(char));
	if (line == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	while ((ch = fgetc(file)) != EOF)
	{
		if (ch == '\n')
		{
			if (bytecodes_count >= bytecodes_size)
			{
				bytecodes_size *= 2;
				bytecodes = realloc(bytecodes, bytecodes_size * sizeof(char *));
				if (bytecodes == NULL)
				{
					fprintf(stderr, "Error: realloc failed\n");
					exit(EXIT_FAILURE);
				}
			}
			line[line_length] = '\0';
			bytecodes[bytecodes_count] = strdup(line);
			if (bytecodes[bytecodes_count] == NULL)
			{
				fprintf(stderr, "Error: strdup failed\n");
				exit(EXIT_FAILURE);
			}
			line_length = 0;
			bytecodes_count++;
		}
		else
		{
			line[line_length++] = ch;
			if (line_length >= len)
			{
				len += 128;
				line = realloc(line, len * sizeof(char));
				if (line == NULL)
				{
					fprintf(stderr, "Error: realloc failed\n");
					exit(EXIT_FAILURE);
				}
			}
		}
	}
	bytecodes[bytecodes_count] = NULL;
	free(line);
	return (bytecodes);
}

/**
 * execute_bytecodes - Execute Monty bytecodes
 * @bytecodes: Array of strings containing Monty bytecodes
 * @stack: Pointer to the stack
 */

void execute_bytecodes(char **bytecodes, stack_t **stack)
{
	unsigned int line_number = 1;
	unsigned int i = 0;
	int j;
	int found = 0;

	for (i = 0; bytecodes[i] != NULL; i++)
	{
		char *opcode, *arg;

		opcode = strtok(bytecodes[i], " \t\n");
		if (opcode == NULL || opcode[0] == '#')
			continue;

		arg = strtok(NULL, " \t\n");

		if (strcmp(opcode, "push") == 0)
		{
			if (arg == NULL)
			{
				fprintf(stderr, "L%u: usage: push integer\n", line_number);
				exit(EXIT_FAILURE);
			}
			push(stack, line_number);
			line_number++;
			continue;
		}

		found = 0;
		for (j = 0; instruction_s[j].opcode != NULL; j++)
		{
			if (strcmp(opcode, instruction_s[j].opcode) == 0)
			{
				found = 1;
				instruction_s[j].f(stack, line_number);
				break;
			}
		}

		if (found == 0)
		{
			fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
			exit(EXIT_FAILURE);
		}

		line_number++;
	}
}

/**
 * monty - Interpret Monty bytecodes from a file
 * @filename: Path to the file containing Monty bytecodes
 *
 * Description: The monty function reads the bytecodes from the
 * given file, interprets and executes them line by line.
 */
void monty(char *filename)
{
	FILE *file;
	char **bytecodes;
	stack_t *stack = NULL;
	unsigned int i;

	file = fopen(filename, "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	bytecodes = read_bytecodes(file);
	fclose(file);

	execute_bytecodes(bytecodes, &stack);

	for (i = 0; bytecodes[i] != NULL; i++)
		free(bytecodes[i]);
	free(bytecodes);
}
