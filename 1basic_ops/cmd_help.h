bool fs_help(char object[], char args[],fs_Directory *root){
    if(strstr(args,"hs"))
    {
        printf("\nhelp: help [-h -hs] [pattern...]\n");
        return true;
    }
    if(strstr(args,"h"))
    {
        printf("\n\
help: help [-h -hs]\n\
    Display information about commands.\n\n\
    Displays brief summaries of builtin commands.\n\
    Can be invoked on any command by using the -h modifier\n");
        return true;
    } else if(strstr(object,"quit"))
    {
        fs_quit("","-h");
        return true;
    } else if(strstr(object,"create"))
    {
        fs_create("","-h",root);
        return true;
    } else if(strstr(object,"delete"))
    {
        fs_delete("","-h",root);
        return true;
    } else if(strstr(object,"save"))
    {
        fs_save("","-h");
        return true;
    } else if(strstr(object,"exit"))
    {
        fs_exit("","-h");
        return true;
    }
    fs_help("","hs",root);
    fs_save("","hs");
    fs_create("","hs",root);
    fs_delete("","hs",root);
    fs_quit("","hs");
    fs_exit("","hs");
    
    return true;
}