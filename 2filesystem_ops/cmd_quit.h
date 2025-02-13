/* Function to handle the 'quit' command, which exits the file manager */
bool fs_quit(char object[], char args[]) {

    /* Check if the user requested the 'hs' flag for a short help message */
    if (strstr(args, "hs")) {
        printf("\nquit: quit [-h -hs -f -s]\n");  /* Print basic usage for the 'quit' command */
        return true;  /* Return true to continue program */
    }

    /* Check if the user requested the '-h' flag for a detailed help message */
    if (strstr(args, "h")) {
        printf("\n\
quit: quit [-h -hs -f -s]\n\
    Exit the file manager.\n\n\
    Exits the file manager gracefully and prompts the user if they want to save the filesystem.\n\
        -f: Forces the filesystem to quit without saving\n\
        -s: Saves the filesystem and quits without prompting the user\n");  /* Print detailed help message for the 'quit' command */
        return true;  /* Return true to continue program */
    }
    if (strstr(args, "f")) { /* Forces the filesystem to quit ungracefuly */
        return false;  /* Return false to quit the filesystem */
    }
    if (strstr(args, "s")) { /* Forces the filesystem to quit gracefuly */
        bool stop = fs_save("", "");  /* Save the filesystem */
        return stop;  /* Return the status of fs_save (false if successful, true if not) */
    }
    while(true){
        printf("Would you like to save the filesystem?(Y/N)\n\t>");
        int choice = scanf(" %c");
        if(choice=='Y'||choice=='y'){
            bool stop = fs_save("","");
            return stop;
        } else if (choice=='N'||choice=='n')
        {
            return false;
        }
        printf("\nBad option, please reenter:\n");
    }
}
