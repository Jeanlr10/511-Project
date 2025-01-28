#include "../2filesystem_ops/create_filesystem.h"
bool fs_cfile(char object[], char args[],fsfolder parentf)
{
    if(strlen(object)<33)
    {
        int i = 0;
        while(parentf.children[i]!=NULL)
        {
            i++;
        }
        parentf.children[i] =(fsfile){.name};
    }    
}