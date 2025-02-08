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
    strcpy(dirname,object);
    if (dirname == NULL || strlen(dirname) == 0) {
        printf("Error: Invalid filename.\n");
    }
    int i;
    bool alreadyexists = false;
    for (i = 0; i < workingdir->child_count; i++) {
        if (workingdir->child[i] != NULL && strcmp(workingdir->child[i]->name, dirname) == 0){
            printf("Error: File '%s' already exists.\n", dirname);
            alreadyexists=true;
        }
    }
    if(!alreadyexists){
        if (workingdir->child_count >= MAX_FILES) {
            printf("Error: Maximum directory limit reached.\n");
        }
        fs_Directory *newdir = malloc(sizeof(fs_Directory));
        if (newdir == NULL) {
            printf("Memory allocation failed.\n");
            return false;
        }
        strcpy(newdir->name, dirname);
        newdir->child[0] = workingdir;
        workingdir->child[workingdir->child_count] = newdir;
        
        workingdir->child_count++;

        printf("Directory '%s' created successfully.\n", dirname);
    }
    return true;
}
