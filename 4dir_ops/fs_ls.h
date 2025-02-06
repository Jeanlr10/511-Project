bool fs_ls(char object[], char args[],fs_Directory *workingdir) {
    if(strstr(args,"hs"))
    {
        printf("\nls: ls [-h -hs]\n");
        return true;
    }
    if(strstr(args,"h"))
    {
        printf("\n\
ls: ls [-h -hs]\n\
    Returns all files and directories in the current directory.\n\n");
        return true;
    }
    int i;
    for(i=0;i++;i<MAX_FILES-1)
    {
        if(workingdir->files[i].name!=NULL)
        {
            printf("%s  %d\n",workingdir->files[i].name,i);
        }
        
    }
    for(i=0;i++;i<MAX_FILES-1)
    {
        if(workingdir->files[i].name!=NULL)
        {
            printf("%s  %d\n",workingdir->files[i].name,i);
        }
        
    }
    return true;
}