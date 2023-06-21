#include "monty.h"

/**
 * add - Adds the top two elements of the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the add opcode is encountered.
 *
 * Description: The add opcode adds the top two elements of the stack.
 * If the stack contains less than two elements, it prints an error message
 * to stderr and exits with EXIT_FAILURE. The result is stored in the second
 * top element of the stack, and the top element is removed.
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *top = *stack;
	stack_t *second = (*stack)->next;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	second->n += top->n;

	*stack = second;
	second->prev = NULL;
	free(top);
}

/**
 * nop - Does nothing.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the nop opcode is encountered.
 *
 * Description: The nop opcode doesn't perform any operations. It is used
 * as a placeholder or for alignment purposes in the Monty bytecode file.
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
	/* Do nothing */
}
