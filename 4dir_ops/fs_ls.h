bool fs_ls(char object[], char args[], fs_Directory *workingdir) {
    /* Check if 'hs' (help short) is provided in the arguments */
    if (strstr(args, "hs")) {
        printf("\nls: ls [-h -hs]\n");
        return true;
    }

    /* Check if 'h' (help) is provided in the arguments */
    if (strstr(args, "h")) {
        printf("\n\
ls: ls [-h -hs]\n\
    Returns all files and directories in the current directory.\n\n");
        return true;
    }

    /* Print the list of directories */
    int i = 0;
    printf("Directories:\n");

    /* Loop through the child directories in the working directory */
    for (i = 0; i < MAX_FILES - 1; i++) {
        /* Check if the child directory exists (non-null) */
        if (workingdir->child[i] && workingdir->child[i]->name != NULL) {
            /* Print the directory name with color formatting */
            printf(BLUE "\t%s" RESET, workingdir->child[i]->name);
        }
    }

    /* Print the list of files */
    printf("\nFiles:\n");

    /* Loop through the files in the working directory */
    for (i = 0; i < MAX_FILES - 1; i++) {
        /* Check if the file has a name (not empty) */
        if (workingdir->files[i].name[0] != '\0') {
            /* Print the file name */
            printf("\t%s", workingdir->files[i].name);
        }
    }

    return true;  /* Return true to indicate that the listing operation has completed */
}
