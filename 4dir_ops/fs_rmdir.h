bool fs_rmdir(char object[], char args[],fs_Directory *workingdir){
    if(strstr(args,"hs"))
    {
        printf("\nrmdir: rmdir [directory name] [-h -hs]\n");
        return true;
    }
    if(strstr(args,"h"))
    {
        printf("\n\
rmdir: rmdir [directory name] [-h -hs]\n\
    Removes a directory with given name if it exists.\n\n");
        return true;
    }
    char dirname[strlen(object)];
    strcpy(dirname,object);
    if (dirname == NULL || strlen(dirname) == 0) {
        printf("Error: Invalid filename.\n");
    }
    int i;
    int folder_index=-1;
    for (i = 0; i < workingdir->child_count; i++) {
        if (workingdir->child[i] != NULL && strcmp(workingdir->child[i]->name, dirname) == 0){
            folder_index=i;
        }
    }
    if(folder_index==-1){
        printf("\nFolder not found\n");
    }
    else{
        for (i = folder_index; i < workingdir->child_count - 1; i++) {
            workingdir->child[i] = workingdir->child[i + 1];
        }
        if(workingdir->child_count==1){
            free(workingdir->child[1]);
        }
        workingdir->child_count=workingdir->child_count-1;
    }
    return true;
}