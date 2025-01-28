#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool fs_save(char object[], char args[]) {
    if(strstr(args,"hs"))
    {
        printf("\nsave: save [-h -hs]\n");
        return true;
    }
    if(strstr(args,"h"))
    {
        printf("\n\
save: save [-h -hs]\n\
    Saves the filesystem.\n\n");
        return true;
    }
    FILE *file = fopen("filesystem_state.txt", "w");
    if (!file) {
        printf("Error: Could not save filesystem.\n");
        return false;
    }

    fprintf(file, "/%s", root.name);
    for (int i = 0; i < root.file_count; i++) {
        fprintf(file, "#%s\n", root.files[i].name);
    }

    fclose(file);
    printf("Filesystem saved successfully.\n");
    return true;
}