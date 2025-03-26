#ifndef FS_INIT_H
#define FS_INIT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

/* Function to initialize the filesystem */
void fs_init() {
    /* Initialize the root directory */
    strcpy(root.name, "root");  /* Set the root directory name */
    root.file_count = 0;  /* Initialize file count to 0 */
    root.child_count = 0;  /* Initialize child count to 0 */
    root.parent = NULL;    /* Root has no parent */
    
    /* Add self-reference as first child */
    root.child[0] = &root;
    root.child_count = 1;
    
    /* Set current directory to root */
    current_dir = &root;
    
    /* Try to restore from the default backup location */
    const char *backup_path = "./fs_metadata.bin";
    struct stat st = {0};
    
    if (stat(backup_path, &st) == 0) {
        /* Backup exists, try to restore it */
        char restore_cmd[256] = "restore";
        fs_restore(restore_cmd, "");
    } else {
        printf("No existing backup found. New filesystem initialized.\n");
    }
}

#endif /* FS_INIT_H */