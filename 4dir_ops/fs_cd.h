#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool fs_cd(char object[], char args[], fs_Directory **workingdir) {
    if (strstr(args, "hs")) {
        printf("\ncd: cd [directory name] [-h -hs]\n");
        return true;
    }
    if (strstr(args, "h")) {
        printf("\n\
cd: cd [directory name] [-h -hs]\n\
    Changes active directory to one with the given name if it exists.\n\n");
        return true;
    }

    if (object == NULL || strlen(object) == 0) {
        printf("Error: Invalid directory name.\n");
        return false;
    }

    char dirname[strlen(object) + 1];  /* Ensure space for null terminator*/
    strcpy(dirname, object);

    /* Handle ".." for moving to the parent directory*/
    if (strcmp(dirname, "..") == 0) {
        workingdir = &(*workingdir)->child[0];
        return true;
    }

    /* Search for the directory in children*/
    int i;
    int folder_index = -1;
    for (i = 0; i < (*workingdir)->child_count; i++) {
        if ((*workingdir)->child[i] != NULL && strcmp((*workingdir)->child[i]->name, dirname) == 0) {
            folder_index = i;
            break;
        }
    }

    if (folder_index == -1) {
        printf("Error: Folder not found.\n");
        return false;
    } else {
        *workingdir = (*workingdir)->child[folder_index];
    }

    return true;
}
