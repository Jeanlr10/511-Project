
bool fs_quit(char object[], char args[]){
    if(strstr(args,"hs"))
    {
        printf("\nquit: quit [-h -hs]\n");
        return true;
    }
    if(strstr(args,"h"))
    {
        printf("\n\
quit: quit [-h -hs]\n\
    Exit the file manager.\n\n\
    Exits the file manager gracefully and saves the filesystem.\n");
        return true;
    }
    bool stop = fs_save("a","q");
    return stop;
}