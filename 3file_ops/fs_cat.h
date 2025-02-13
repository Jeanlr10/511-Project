
bool fs_cat(char object[], char args[], fs_Directory *workingdir) {
    /* Check if 'hs' (help short) is provided in the arguments */
    if(strstr(args,"hs"))
    {
        printf("\ncat: cat [filename] [-h -hs]\n");
        return true;
    }

    /* Check if 'h' (help) is provided in the arguments */
    if(strstr(args,"h"))
    {
        printf("\n\
cat: Cat [FILE] [-h -hs]\n\
    Views the contents of a FILE if it exists.\n\n");
        return true;
    }
    char filename[strlen(object)];
    strcpy(filename, object);
    /* Check if the filename is invalid (NULL or empty) */
    if (filename == NULL || strlen(filename) == 0) {
        printf("Error: Invalid filename.\n");
        return true;  /* Return false to indicate an error */
    }

    /* Check if a file with the name exists in the directory */
    int i;
    for (i = 0; i < workingdir->file_count; i++) {
        if (strcmp(workingdir->files[i].name, filename) == 0) {
            printf("%s\n", workingdir->files[i].content); /* prints the content of the file */
            return true;  /* Return true to continue the program */
        }
    }

    /* Print a failure message */
    printf("File '%s' doesn't exist.\n", filename);
    return true;  /* Return true indicating the file was created successfully */
}
