#include "monty.h"

/**
 * main - Entry point of the program
 * @argc: Argument count
 * @argv: Array of pointers to the arguments
 *
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	monty(argv[1]);

	return (0);
}
