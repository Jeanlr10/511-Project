'''bool fs_renamedir(char object[], char args[], fs_Directory *workingdir) {
    /* Check if 'hs' (help short) is provided in the arguments */
    if (strstr(args, "hs") && strstr(args, "hs") == args) {
        printf("\nrename: rename [filename] [-h -hs]\n");
        return true;
    }

    /* Check if 'h' (help) is provided in the arguments */
    if (strstr(args, "h") && strstr(args, "h") == args) {
        printf("\n\
rename: rename [filename] [-h -hs]\n\
    Renames a file [filename]. If the new filename already exists, it will not be overwritten.\n");
        return true;
    }

    fs_File *editfile = NULL;

    /* Find the file in the directory */
    for (int i = 0; i < workingdir->file_count; i++) {
        if (strcmp(workingdir->files[i].name, object) == 0) {
            editfile = &workingdir->files[i];
            break;
        }
    }

    if (editfile == NULL) {
        printf("File not found: %s\n", object);
        return true;
    }

    printf("Please enter the new filename:\n\t- ");
    char choice[50]; /* Store the character input */
    int result = scanf("%49s", choice); /* Read input correctly, limiting to 49 characters */

    /* Clear remaining input buffer */
    while (getchar() != '\n');

    if (result != 1) {
        printf("Invalid input for filename.\n");
        return true;
    }

    /* Check if the new filename already exists */
    for (int i = 0; i < workingdir->file_count; i++) {
        if (strcmp(workingdir->files[i].name, choice) == 0) {
            printf("Error: A file with that name already exists.\n");
            return true;
        }
    }

    /* Rename file safely */
    strncpy(editfile->name, choice, sizeof(editfile->name) - 1);
    editfile->name[sizeof(editfile->name) - 1] = '\0'; /* Ensure null termination */

    printf("File renamed to: %s\n", editfile->name);

    return true;
}
'''