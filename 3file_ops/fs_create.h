#include <stdio.h>
#include <string.h>

bool fs_create(char object[], char args[], fs_Directory *workingdir) {
    /* Check if 'hs' (help short) is provided in the arguments */
    if(strstr(args,"hs"))
    {
        printf("\ncreate: create [filename] [-h -hs]\n");
        return true;
    }

    /* Check if 'h' (help) is provided in the arguments */
    if(strstr(args,"h"))
    {
        printf("\n\
create: create [FILE] [-h -hs]\n\
    Creates a FILE if it does not already exist.\n\n");
        return true;
    }

    /* Create a filename variable based on the object input (i.e., file name) */
    char filename[strlen(object)];
    strcpy(filename, object);

    /* Check if the filename is invalid (NULL or empty) */
    if (filename == NULL || strlen(filename) == 0) {
        printf("Error: Invalid filename.\n");
        return false;  /* Return false to indicate an error */
    }

    /* Check if a file with the same name already exists in the directory */
    int i;
    for (i = 0; i < workingdir->file_count; i++) {
        if (strcmp(workingdir->files[i].name, filename) == 0) {
            printf("Error: File '%s' already exists.\n", filename);
            return true;  /* Return true to continue the program */
        }
    }

    /* Check if the maximum number of files has been reached in the directory */
    if (workingdir->file_count >= MAX_FILES) {
        printf("Error: Maximum file limit reached.\n");
        return true;  /* Return true to continue the program */
    }

    /* Create the new file by assigning the filename and initializing the content */
    strcpy(workingdir->files[workingdir->file_count].name, filename);
    workingdir->files[workingdir->file_count].content[0] = '\0';  /* Initialize with empty content */
    
    /* Increment the file count to reflect the new file in the directory */
    workingdir->file_count++;

    /* Print a success message */
    printf("File '%s' created successfully.\n", filename);
    return true;  /* Return true to continue the program */
}
