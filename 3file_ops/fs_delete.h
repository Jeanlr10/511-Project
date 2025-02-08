#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool fs_delete(char object[], char args[], fs_Directory *workingdir) {
    /* Check if 'hs' (help short) is provided in the arguments */
    if (strstr(args, "hs")) {
        printf("\ndelete: delete [filename] [-h -hs]\n");
        return true;
    }

    /* Check if 'h' (help) is provided in the arguments */
    if (strstr(args, "h")) {
        printf("\n\
delete: delete [FILE] [-h -hs]\n\
    Deletes a FILE if it exists.\n\
    If no FILE is specified, the most recent file created will be removed\n");
        return true;
    }

    /* Create a filename variable based on the object input (i.e., file name) */
    char filename[strlen(object)];
    strcpy(filename, object);

    /* Check if the filename is invalid (NULL or empty) */
    if (filename == NULL || strlen(filename) == 0) {
        printf("Error: Invalid filename.\n");
        return true;  /* Return true as the input is invalid but we don’t exit the program */
    }

    /* Try to find the file in the working directory */
    int file_index = -1;
    int i;
    for (i = 0; i < workingdir->file_count; i++) {
        /* If the file is found, store the index and break out of the loop */
        if (strcmp(workingdir->files[i].name, filename) == 0) {
            file_index = i;
            break;
        }
    }

    /* If file_index is still -1, the file was not found */
    if (file_index == -1) {
        printf("Error: File '%s' not found.\n", filename);
        return true;  /* Return true to indicate that we finished handling the request */
    }

    /* Shift the remaining files to fill the gap after the deleted file */
    for (i = file_index; i < workingdir->file_count - 1; i++) {
        workingdir->files[i] = workingdir->files[i + 1];
    }

    /* Decrease the file count to reflect the file removal */
    workingdir->file_count--;

    /* Print a success message */
    printf("File '%s' deleted successfully.\n", filename);
    return true;  /* Return true indicating the file was deleted successfully */
}
