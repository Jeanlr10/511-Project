/* Function to handle the 'help' command, providing help on various commands */
bool fs_help(char object[], char args[], fs_Directory *root) {
    /* Check if the user requested help with the 'hs' flag (short help operator) */
    if (strstr(args, "hs")) {
        printf("\nhelp: help [-h -hs] [pattern...]\n");  /* Print basic usage for 'help' command */
        return true;  /* Return true to indicate help was shown */
    }
    
    /* Check if the user requested help with the '-h' flag */
    if (strstr(args, "h")) {
        printf("\n\
help: help [-h -hs]\n\
    Display information about commands.\n\n\
    Displays brief summaries of builtin commands.\n\
    Can be invoked on any command by using the -h modifier\n");  /* Print detailed help message for 'help' command */
        return true;  /* Return true to indicate help was shown */
    }

    /* If the object is 'quit', call fs_quit to provide help for that command */
    else if (strstr(object, "quit")) {
        fs_quit("", "-h");  /* Show help for 'quit' command */
        return true;  /* Return true to indicate help was shown */
    }

    /* If the object is 'create', call fs_create to provide help for that command */
    else if (strstr(object, "create")) {
        fs_create("", "-h", root);  /* Show help for 'create' command */
        return true;  /* Return true to indicate help was shown */
    }

    /* If the object is 'delete', call fs_delete to provide help for that command */
    else if (strstr(object, "delete")) {
        fs_delete("", "-h", root);  /* Show help for 'delete' command */
        return true;  /* Return true to indicate help was shown */
    }

    /* If the object is 'save', call fs_save to provide help for that command */
    else if (strstr(object, "save")) {
        fs_save("", "-h");  /* Show help for 'save' command */
        return true;  /* Return true to indicate help was shown */
    }

    /* If the object is 'exit', call fs_exit to provide help for that command */
    else if (strstr(object, "exit")) {
        fs_exit("", "-h");  /* Show help for 'exit' command */
        return true;  /* Return true to indicate help was shown */
    }

    /* If no specific command is matched, show help for all relevant commands */
    fs_help("", "hs", root);  /* Show short help for help */
    fs_save("", "hs");  /* Show short help for save */
    fs_create("", "hs", root);  /* Show short help for 'create' */
    fs_delete("", "hs", root);  /* Show short help for 'delete' */
    fs_cat("", "hs",root);
    fs_pwd("", "hs",root);
    fs_mkdir("", "hs",root);
    fs_rmdir("", "hs",root);
    fs_ls("", "hs",root);
    fs_cd("", "hs",root);
    fs_quit("", "hs");  /* Show short help for 'quit' */
    
    
    return true;  /* Return true to indicate help was shown */
}
