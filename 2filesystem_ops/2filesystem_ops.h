
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_FILES 100     /* Maximum number of files or directories in a directory */
#define MAX_FILENAME 50   /* Maximum length of a file or directory name */
#define FILE_CONTENT_SIZE 1024  /* Maximum size of file content */

/* Forward declaration of fs_Directory structure */
typedef struct fs_Directory fs_Directory; 

/* Definition of fs_File structure to represent a file */
typedef struct {
    char name[MAX_FILENAME];   /* Name of the file */
    char content[FILE_CONTENT_SIZE]; /* Content of the file (up to 1024 characters) */
} fs_File;

/* Definition of fs_Directory structure representing a directory */
typedef struct fs_Directory {
    char name[MAX_FILENAME];   /* Name of the directory */
    fs_File files[MAX_FILES];  /* Array of files in the directory */
    int file_count;            /* Number of files in the directory */
    int child_count;           /* Number of child directories */
    fs_Directory *parent;      /* Pointer to the parent directory */
    fs_Directory *child[MAX_FILES]; /* Array of child directories */
};

/* Global variables */
fs_Directory root;    /* The root directory */
fs_Directory *current_dir; /* Current working directory */

#include "cmd_restore.h"
#include "fs_init.h"
#include "cmd_save.h"
#include "cmd_pwd.h"
#include "cmd_quit.h"