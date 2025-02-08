bool fs_ls(char object[], char args[],fs_Directory *workingdir) {
    printf("2");
    if(strstr(args,"hs"))
    {
        printf("\nls: ls [-h -hs]\n");
        return true;
    }
    printf("2");
    if(strstr(args,"h"))
    {
        printf("\n\
ls: ls [-h -hs]\n\
    Returns all files and directories in the current directory.\n\n");
        return true;
    }
    printf("2");
    int i=0;
    printf("First Loop");
    for(i=0;i<MAX_FILES-1;i++) {
        if(workingdir->child[i]->name!=NULL)
        {
            printf("%s\n",workingdir->child[i]->name);
        }
        
    }
    printf("Second loop");
    for(i=0;i<MAX_FILES-1;i++) {
        if(workingdir->files[i].name[0]!='\0')
        {
            printf("%s\n",workingdir->files[i].name);
        }
        
    }
    return true;
}