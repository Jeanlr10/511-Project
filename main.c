#include "./1basic_ops/1basic_ops.h"  /* Includes basic operations header */
#include "./2filesystem_ops/2filesystem_ops.h"  /* Includes filesystem operations header */
#include "./3file_ops/3file_ops.h"  /* Includes file operations header */
#include "./4dir_ops/4dir_ops.h"  /* Includes directory operations header */
/*etc etc etc*/
#include "./1basic_ops/cmd_help.h"  /* Help MUST be loaded last to ensure all functions are available */

int main() {
    fs_init();  /* Initializes the file system */
    
    fs_Directory *workingdir;  /* Pointer to the current working directory */
    workingdir = &root;  /* Set the initial working directory to the root directory */
    
    bool continueprogram = true;  /* Boolean flag to control the program's main loop */
    
    /* Allocates memory for buffers to store user input */
    char *command = (char *)malloc(256 * sizeof(char)); /* Buffer for full input */
    char *operation = (char *)malloc(64 * sizeof(char)); /* Buffer for the operation (command) */
    char *object = (char *)malloc(64 * sizeof(char)); /* Buffer for the object (filename, directory, etc.) */
    char *args = (char *)malloc(128 * sizeof(char)); /* Buffer for additional arguments */
    
    /* Check for memory allocation failure */
    if (!command || !operation || !object || !args) {
        fprintf(stderr, "Memory allocation failed.\n");  /* Print error message if allocation fails */
        return 1;  /* Exit program if allocation fails */
    }

    printf("Welcome to the File system!\nEnter a command or type 'help' for assistance.\n");

    while (continueprogram) {  /* Main loop for handling commands */
        printf("\n> ");  /* Prompt user for input */
        
        /* Read user input */
        if (fgets(command, 256, stdin) == NULL) {
            fprintf(stderr, "Error reading input.\n");  /* Print error message if input fails */
            break;  /* Exit loop on input failure */
        }

        /* Remove trailing newline character from input */
        command[strcspn(command, "\n")] = '\0';

        /* Initialize buffers to empty strings */
        operation[0] = '\0';  /* Clear the operation buffer */
        object[0] = '\0';  /* Clear the object buffer */
        args[0] = '\0';  /* Clear the arguments buffer */

        /* Parse input into operation, object, and arguments */
        int items_parsed = sscanf(command, "%s %s %[^\n]", operation, object, args);

        /* If arguments are provided, extract those starting with '-' */
        if (items_parsed >= 2) {
            char *args_start = strchr(command, '-');
            if (args_start != NULL) {
                strncpy(args, args_start + 1, sizeof(args) - 1);  /* Capture everything after '-' */
            }
        }
        
        /* Debug: Uncomment to print parsed input values for testing purposes */
        /* printf("%s\n%s\n%s\n", command, object, args); */
        /*printf("%d\n", strhash(operation)); /**/

        /* Handle operation based on the hashed value of the command */
        switch(strhash(operation)){
            case 8397:  /* 'help' command */
                continueprogram = fs_help(object, args, &root);
                break;
            case 42392:  /* 'hello' command */
                continueprogram = hello(object, args);
                break;
            case 10342:  /* 'quit' command */
                continueprogram = fs_quit(object, args);
                break;
            case 247417:  /* 'create' command */
                continueprogram = fs_create(object, args, workingdir);
                break;
            case 211667:  /* 'delete' command */
                continueprogram = fs_delete(object, args, workingdir);
                break;
            case 8092:  /* 'save' command */
                fs_save(object, args);
                break;
            case 10717:  /* 'exit' command */
                continueprogram = fs_quit(object, args);
                break;
            case 1987:  /* 'pwd' command */
                continueprogram = fs_pwd(object, args, workingdir);
                break;
            case 287:  /* 'ls' command */
                continueprogram = fs_ls(object, args, workingdir);
                break;
            case 45082:  /* 'mkdir' command */
                continueprogram = fs_mkdir(object, args, workingdir);
                break;
            case 46332:  /* Another 'mkdir' command (seems redundant) */
                continueprogram = fs_mkdir(object, args, workingdir);
                break;
            case 8217:
                continueprogram = fs_edit(object,args,workingdir);
                break;/**/
            case 1517:
                fs_cat(object,args,workingdir);
                break;
            case 212:
                fs_cd(object,args,&workingdir);
                break;
            default:  /* If command is not recognized */
                printf("Command not found. Type 'help' for assistance.");
        }
    }

    /* Free dynamically allocated memory */
    free(command);
    free(operation);
    free(object);
    free(args);

    return 0;  /* Exit program */
}