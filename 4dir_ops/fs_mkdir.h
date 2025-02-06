#include <stdio.h>
#include <string.h>

bool fs_mkdir(char object[], char args[], fs_Directory *workingdir) {
    if(strstr(args,"hs"))
    {
        printf("\nmkdir: mkdir [directory name] [-h -hs]\n");
        return true;
    }
    if(strstr(args,"h"))
    {
        printf("\n\
nmkdir: mkdir [directory name] [-h -hs]\n\
    Creates a directory with given name if it does not already exist.\n\n");
        return true;
    }
    char dirname[strlen(object)];
    printf("%s\n",dirname);
    strcpy(dirname,object);
    if (dirname == NULL || strlen(dirname) == 0) {
        printf("Error: Invalid filename.\n");
    }
    int i;
    for (i = 0; i < workingdir->file_count; i++) {
        if (strcmp(workingdir->child[i]->name, dirname) == 0) {
            printf("Error: File '%s' already exists.\n", dirname);
        }
    }
    if (workingdir->child_count >= MAX_FILES) {
        printf("Error: Maximum file limit reached.\n");
    }
    fs_Directory newdir;
    strcpy(newdir.name, dirname);
    workingdir->child[workingdir->child_count]=&newdir;
    
    workingdir->child_count++;

    printf("Directory '%s' created successfully.\n", dirname);
}
