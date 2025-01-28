bool help(char object[], char args[]){
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
    } else if(strstr(args,"quit"))
    {
        quit("","-h");
        return true;
    }
    help("","hs");
    quit("","hs");
    return true;
}