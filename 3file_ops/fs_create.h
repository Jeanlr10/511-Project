#include <stdio.h>
#include <string.h>
bool fs_create(char object[], char args[]) {
    if(strstr(args,"hs"))
    {
        printf("\ncreate: create [filename] [-h -hs]\n");
        return true;
    }
    if(strstr(args,"h"))
    {
        printf("\n\
create: create [FILE] [-h -hs]\n\
    Creates a FILE if it does not already exist.\n\n");
        return true;
    }
    char filename[strlen(object)];
    strcpy(filename,object);
    if (filename == NULL || strlen(filename) == 0) {
        printf("Error: Invalid filename.\n");
    }
    for (int i = 0; i < root.file_count; i++) {
        if (strcmp(root.files[i].name, filename) == 0) {
            printf("Error: File '%s' already exists.\n", filename);
        }
    }
    if (root.file_count >= MAX_FILES) {
        printf("Error: Maximum file limit reached.\n");
    }
    strcpy(root.files[root.file_count].name, filename);
    root.files[root.file_count].content[0] = '\0'; 
    root.file_count++;

    printf("File '%s' created successfully.\n", filename);
}