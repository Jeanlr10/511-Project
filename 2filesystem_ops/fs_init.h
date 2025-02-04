#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>



#define MAX_FILES 100
#define MAX_FILENAME 50

typedef struct fs_Directory fs_Directory; 

typedef struct {
    char name[MAX_FILENAME];
    char content[1024]; 
} fs_File;

struct fs_Directory {
    char name[MAX_FILENAME];
    fs_File files[MAX_FILES]; 
    int file_count;
    int child_count;
    fs_Directory *parent;
    fs_Directory *child[MAX_FILES];
};

fs_Directory root;

void fs_init(){
   FILE *file = fopen("filesystem_state.dat", "r");
    if (file) {
        fread(&root, sizeof(fs_Directory), 1, file);
        fclose(file);
        printf("Filesystem loaded successfully.\n");
    } else {
        strcpy(root.name, "root");
        root.file_count = 0;
        printf("New filesystem initialized.\n");

        FILE *new_file = fopen("filesystem_state.dat", "w");
        if (new_file) {
            fwrite(&root, sizeof(fs_Directory), 1, new_file);
            fclose(new_file);
            printf("Filesystem saved for the first time.\n");
        } else {
            printf("Error: Unable to create filesystem file.\n");
        }
    }
}