#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool fs_save(char object[], char args[]) {
    /* Check if 'hs' (help short) is provided in the arguments */
    if(strstr(args,"hs"))
    {
        printf("\nsave: save [-h -hs]\n");
        return true;
    }

    /* Check if 'h' (help) is provided in the arguments */
    if(strstr(args,"h"))
    {
        printf("\n\
save: save [-h -hs]\n\
    Saves the filesystem.\n\n");
        return true;
    }

    /* Attempt to open the file 'filesystem_state.txt' in write mode */
    FILE *file = fopen("filesystem_state.dat", "w");
    if (!file) {
        /* If the file cannot be opened, print an error message */
        printf("Error: Could not save filesystem.\n");
        return true;
    }

    /* Write the root directory name to the file */
    fprintf(file, "Directory: %s\n", root.name);

    /* Loop through each file in the root directory and save its name */
    int i;
    for (i = 0; i < root.file_count; i++) {
        fprintf(file, "File: %s\n", root.files[i].name);
    }

    /* Close the file after writing */
    fclose(file);

    /* Print a success message */
    printf("Filesystem saved successfully.\n");
    return false;  /* Return false indicating the operation was completed */
}

save_directory(fs_Directory **directory){}
save_file(fs_File **file){}