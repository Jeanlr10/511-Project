#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define MAX_FILES 100  /* Maximum number of files or directories in a directory */
#define MAX_FILENAME 50  /* Maximum length of a file or directory name */

/* Forward declaration of fs_Directory structure */
typedef struct fs_Directory fs_Directory; 

/* Definition of fs_File structure to represent a file */
typedef struct {
    char name[MAX_FILENAME];  /* Name of the file */
    char content[1024];  /* Content of the file (up to 1024 characters) */
} fs_File;

/* Definition of fs_Directory structure representing a directory */
struct fs_Directory {
    char name[MAX_FILENAME];  /* Name of the directory */
    fs_File files[MAX_FILES];  /* Array of files in the directory */
    int file_count;  /* Number of files in the directory */
    int child_count;  /* Number of child directories */
    fs_Directory *parent;  /* Pointer to the parent directory */
    fs_Directory *child[MAX_FILES];  /* Array of child directories */
};

fs_Directory root;  /* Declare the root directory */
/* Function to initialize the filesystem */
void fs_init() {
    root.child[0]=&root;
    root.child_count++;
    /* Try to open the filesystem state file to load existing filesystem data */
    FILE *file = fopen("filesystem_state.dat", "r");
    if (file) {
        /* If file exists, load the data into the root directory */
        fread(&root, sizeof(fs_Directory), 1, file);
        fclose(file);
        printf("Filesystem loaded successfully.\n");
    } else {
        /* If the file doesn't exist, initialize the root directory */
        strcpy(root.name, "root");  /* Set the root directory name */
        root.file_count = 0;  /* Initialize file count to 0 */
        printf("New filesystem initialized.\n");

        /* Create a new file to save the initialized filesystem */
        FILE *new_file = fopen("filesystem_state.dat", "w");
        if (new_file) {
            /* Write the root directory structure to the file */
            fwrite(&root, sizeof(fs_Directory), 1, new_file);
            fclose(new_file);
            printf("Filesystem saved for the first time.\n");
        } else {
            /* Handle error if the file cannot be created */
            printf("Error: Unable to create filesystem file.\n");
        }
    }
}
load_directory(){}
load_file(){}