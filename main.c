#include "./1basic_ops/1basic_ops.h"
//#include "./2filesystem_ops/2filesystem_ops.h"
//#include "./3file_ops/3file_ops.h"
//#include "./4dir_ops/3dir_ops.h"
//etc etc etc
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
        
        //useful debug statements
        //printf("%s\n%s\n%s\n",command,object,args);
        printf("%d\n",strhash(operation));
        
        // Handle operation
        
        switch(strhash(operation)){
            case 59592: // help when hashed
                continueprogram=help(object,args);
                break;
            case 596582: // hello when hashed
                continueprogram=hello(object,args);
                break;
            case 75332: // quit when hashed
                continueprogram=quit(object,args);
                break;
            case 722703482:
                //continueprogram=fs_cfile(object,args);
                break;
            default:
                printf("Command not found. Type 'help' for assistance.");
        }
    }

    // Free allocated memory
    free(command);
    free(operation);
    free(object);
    free(args);

    return 0;
}
