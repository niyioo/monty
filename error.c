/**
 * printErrorMessage - Prints appropriate error messages
 * based on the error code.
 * @errorCode: The error codes
 */

void printErrorMessage(int errorCode, ...)
{
        va_list args;
        char *op;
        int lineNum;

        va_start(args, errorCode);
        switch (errorCode)
        {
                case 1:
                        fprintf(stderr, "USAGE: monty file\n");
                        break;
                case 2:
                        fprintf(stderr, "Error: Can't open file %s\n", va_arg(args, char *));
                        break;
                case 3:
                        lineNum = va_arg(args, int);
                        op = va_arg(args, char *);
                        fprintf(stderr, "L%d: unknown instruction %s\n", lineNum, op);
                        break;
                case 4:
                        fprintf(stderr, "Error: malloc failed\n");
                        break;
                case 5:
                        fprintf(stderr, "L%d: usage: push integer\n", va_arg(args, int));
                        break;
                default:
                        break;
        }
        free_nodes();
        va_end(args);
        exit(EXIT_FAILURE);
}

/**
 * more_err - Handles errors.
 * @errorCode: The error codes
 */

void more_err(int errorCode, ...)
{
        va_list args;
        char *op;
        int lineNum;

        va_start(args, errorCode);
        switch (errorCode)
        {
                case 6:
                        fprintf(stderr, "L%d: can't pint, stack empty\n", va_arg(args, int));
                        break;
                case 7:
                        fprintf(stderr, "L%d: can't pop an empty stack\n", va_arg(args, int));
                        break;
                case 8:
                        lineNum = va_arg(args, unsigned int);
                        op = va_arg(args, char *);
                        fprintf(stderr, "L%d: can't %s, stack too short\n", lineNum, op);
                        break;
                case 9:
                        fprintf(stderr, "L%d: division by zero\n", va_arg(args, unsigned int));
                        break;
                default:
                        break;
        }
        free_nodes();
        va_end(args);
        exit(EXIT_FAILURE);
}

/**
 * string_err - Handles errors related to strings.
 * @errorCode: The error codes.
 */

void string_err(int errorCode, ...)
{
        va_list args;
        int lineNum;

        va_start(args, errorCode);
        lineNum = va_arg(args, int);
        switch (errorCode)
        {
                case 10:
                        fprintf(stderr, "L%d: can't pchar, value out of range\n", lineNum);
                        break;
                case 11:
                        fprintf(stderr, "L%d: can't pchar, stack empty\n", lineNum);
                        break;
                default:
                        break;
        }
        free_nodes();
        va_end(args);
        exit(EXIT_FAILURE);
}
