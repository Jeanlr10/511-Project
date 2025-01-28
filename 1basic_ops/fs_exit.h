
bool fs_exit(char object[], char args[]){
    if(strstr(args,"hs"))
    {
        printf("\exit: exit [-h -hs]\n");
        return true;
    }
    if(strstr(args,"h"))
    {
        printf("\n\
exit: exit [-h -hs]\n\
    Exits the file manager and ignores all changes to the filesystem.\n");
        return true;
    }
    bool stop = fs_save("a","q");
    return !stop;
}