#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool fs_pwd(char object[], char args[],fs_Directory *workingdir) {
    if(strstr(args,"hs"))
    {
        printf("\npwd: pwd [-h -hs]\n");
        return true;
    }
    if(strstr(args,"h"))
    {
        printf("\n\
pwd: pwd [-h -hs]\n\
    Returns the current directory.\n\n");
        return true;
    }
    printf("%s\n",workingdir);
}