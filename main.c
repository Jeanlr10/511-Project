
#include "./2filesystem_ops/2filesystem_ops.h"
#include "./3file_ops/3file_ops.h"
#include "./4dir_ops/4dir_ops.h"
/*etc etc etc*/
#include "./1basic_ops/1basic_ops.h"
int main() {
    fs_init();
    fs_Directory *workingdir;
    workingdir=&root;
    bool continueprogram = true;
    char *command = (char *)malloc(256 * sizeof(char)); /* Buffer for full input*/
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

        /* Remove trailing newline*/
        command[strcspn(command, "\n")] = '\0';

        /* Initialize components*/
        operation[0] = '\0';
        object[0] = '\0';
        args[0] = '\0';

        /* Parse input*/
        int items_parsed = sscanf(command, "%s %s %[^\n]", operation, object, args);

        if (items_parsed >= 2) {
            char *args_start = strchr(command, '-');
            if (args_start != NULL) {
                strncpy(args, args_start + 1, sizeof(args) - 1); /* Capture everything after '-'*/
            }
        }
        
        /*useful debug statements*/
        /*printf("%s\n%s\n%s\n",command,object,args);*/
        /*printf("%d\n",strhash(operation));*/
        
        /* Handle operation*/
        
        switch(strhash(operation)){
            case 8397: /* help when hashed*/
                continueprogram=fs_help(object,args,&root);
                break;
            case 42392: /* hello when hashed*/
                continueprogram=hello(object,args);
                break;
            case 10342: /* quit when hashed*/
                continueprogram=fs_quit(object,args);
                break;
            case 247417:
                continueprogram=fs_create(object,args,workingdir);
                break;
            case 211667:
                continueprogram=fs_delete(object,args,workingdir);
                break;
            case 8092:
                fs_save(object,args);
                break;
            case 10717:
                continueprogram=fs_exit(object,args);
                break;
            case 1987:
                continueprogram=fs_pwd(object,args,workingdir);
                break;
            case 287:
                continueprogram=fs_ls(object,args,workingdir);
                break;
            case 45082:
                continueprogram=fs_mkdir(object,args,workingdir);
            default:
                printf("Command not found. Type 'help' for assistance.");
        }
    }

    /* Free allocated memory*/
    free(command);
    free(operation);
    free(object);
    free(args);

    return 0;
}
