/* Function to handle the 'quit' command, which exits the file manager */
bool fs_quit(char object[], char args[]) {
    /* Check if the user requested the 'hs' flag for a short help message */
    if (strstr(args, "hs")) {
        printf("\nquit: quit [-h -hs]\n");  /* Print basic usage for the 'quit' command */
        return true;  /* Return true to indicate help was shown */
    }

    /* Check if the user requested the '-h' flag for a detailed help message */
    if (strstr(args, "h")) {
        printf("\n\
quit: quit [-h -hs]\n\
    Exit the file manager.\n\n\
    Exits the file manager gracefully and saves the filesystem.\n");  /* Print detailed help message for the 'quit' command */
        return true;  /* Return true to indicate help was shown */
    }

    /* Save the filesystem before quitting, passing empty arguments as needed */
    bool stop = fs_save("", "");  /* Save the filesystem */

    return stop;  /* Return the status of fs_save (true if successful, false if not) */
}
