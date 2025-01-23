typedef struct
{
    char name[32];
    struct file *child[128]; 
    struct folder *parent;
} folder;

typedef struct
{
    int size;
    char name[32];
    char* data[];
} file;

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
            folder root=(folder) {.name="root"};
            fwrite(root, sizeof(folder));
        } 
        else
        {
            printf("There was an error in creating the filesystem.");
            return NULL;
        }
    }

}
