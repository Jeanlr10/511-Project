#include "basic_operations.h"
#include "filesystem_operations.h"

int main() {
    bool continueprogram = true;
    char *command = (char *)malloc(256 * sizeof(char)); // Buffer for full input
    char *operation = (char *)malloc(64 * sizeof(char));
    char *object = (char *)malloc(64 * sizeof(char));
    char *args = (char *)malloc(128 * sizeof(char));

    if (!command || !operation || !object || !args) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    printf("Welcome to the File system!\nEnter a command or type 'help' for assistance.\n");

    while (continueprogram) {
        printf("\n> ");
        if (fgets(command, 256, stdin) == NULL) {
            fprintf(stderr, "Error reading input.\n");
            break;
        }

        // Remove trailing newline
        command[strcspn(command, "\n")] = '\0';

        // Initialize components
        operation[0] = '\0';
        object[0] = '\0';
        args[0] = '\0';

        // Parse input
        int items_parsed = sscanf(command, "%s %s %[^\n]", operation, object, args);

        if (items_parsed >= 2) {
            char *args_start = strchr(command, '-');
            if (args_start != NULL) {
                strncpy(args, args_start + 1, sizeof(args) - 1); // Capture everything after '-'
            }
        }
        printf("%s\n%s\n%s\n",command,object,args);

        // Handle operation
        if (strcmp(operation, "quit") == 0) {
            continueprogram = quit(object,args);
        } else if (strcmp(operation, "hello") == 0) {
            continueprogram = hello(object,args);
        } else if (strcmp(operation, "help") == 0) {
            continueprogram = help(object,args);
        } else {
            printf("Command not found. Type 'help' for assistance.\n");
        }
    }

    // Free allocated memory
    free(command);
    free(operation);
    free(object);
    free(args);

    return 0;
}
