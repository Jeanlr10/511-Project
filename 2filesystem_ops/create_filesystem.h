#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
    char name[32];
    struct fsfile *children[128]; 
    struct fsfolder *parent;
} fsfolder;

typedef struct
{
    char name[32];
    char* data[];
} fsfile;

FILE* startfilesystem(){
    if(access("filesystem.fb",'wb'))
    {
        FILE* filesystem = fopen("filesystem.fb",'wb');
        if(filesystem!=NULL)
        {
            return filesystem;
        } 
        else
        {
            printf("There was an error in opening the filesystem.");
            return NULL;
        } 
    }
    else
    {
        FILE* filesystem = fopen("filesystem.fb",'wb');
        if(filesystem!=NULL)
        {
            fsfolder root=(fsfolder) {.name="root"};
            fwrite(&root, sizeof(fsfolder),1,filesystem);
            return filesystem;

        }
        else
        {
            printf("There was an error in creating the filesystem.");
            return NULL;
        }
    }
}