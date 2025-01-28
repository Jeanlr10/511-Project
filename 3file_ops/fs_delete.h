#include <stdio.h>
#include <string.h>
#include <stdbool.h>
bool fs_delete(char object[], char args[]) {
   if(strstr(args,"hs"))
    {
        printf("\ndelete: delete [filename] [-h -hs]\n");
        return true;
    }
    if(strstr(args,"h"))
    {
        printf("\n\
delete: delete [FILE] [-h -hs]\n\
    Deletes a FILE if it exists.\n\
    If no FILE is specified, the most recent file created will be removed\n");
        return true;
    }
    char filename[strlen(object)];
    strcpy(filename,object);
    if (filename == NULL || strlen(filename) == 0) {
        printf("Error: Invalid filename.\n");
        return true;
    }
    int file_index = -1;
    for (int i = 0; i < root.file_count; i++) {
        if (strcmp(root.files[i].name, filename) == 0) {
            file_index = i;
            break;
        }
    }
    if (file_index == -1) {
        printf("Error: File '%s' not found.\n", filename);
        return true;
    }
    for (int i = file_index; i < root.file_count - 1; i++) {
        root.files[i] = root.files[i + 1];
    }
    root.file_count--;
    printf("File '%s' deleted successfully.\n");
    return true;
}