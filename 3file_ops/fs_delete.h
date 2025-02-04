#include <stdio.h>
#include <string.h>
#include <stdbool.h>
bool fs_delete(char object[], char args[],fs_Directory *workingdir) {
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
    int i;
    for (i = 0; i < workingdir->file_count; i++) {
        if (strcmp(workingdir->files[i].name, filename) == 0) {
            file_index = i;
            break;
        }
    }
    if (file_index == -1) {
        printf("Error: File '%s' not found.\n", filename);
        return true;
    }
    for (i = file_index; i < workingdir->file_count - 1; i++) {
        workingdir->files[i] = workingdir->files[i + 1];
    }
    workingdir->file_count--;
    printf("File '%s' deleted successfully.\n");
    return true;
}