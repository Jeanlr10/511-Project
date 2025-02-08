/* Function to handle the 'exit' command */
bool fs_exit(char object[], char args[]){
    /* Check if the user requested help with '-hs' flag */
    if(strstr(args, "hs")) {
        printf("\nexit: exit [-h -hs]\n");  /* Print short help message for 'exit' command */
        return true;  /* Return true to indicate help was shown */
    }
    
    /* Check if the user requested help with '-h' flag */
    if(strstr(args, "h")) {
        printf("\n\
exit: exit [-h -hs]\n\
    Exits the file manager and ignores all unsaved changes to the filesystem.\n");  /* Print detailed help message for 'exit' command */
        return true;  /* Return true to indicate help was shown */
    }

    /* If no help flag is found, just return false to continue execution */
    return false;  /* Return false to indicate no special action (e.g., help) is required */
}
