#ifndef CMD_RESTORE_H
#define CMD_RESTORE_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdint.h>

/* Forward declaration for parent function */
fs_Directory* create_directory(fs_Directory *parent, const char *name);

/* Forward declarations for recursive loading*/
bool load_directory(FILE *file, fs_Directory *parent, int depth);
bool load_file(FILE *file, fs_Directory *directory);

bool fs_restore(char *args, char *object) {
    /* Check if 'hs' (help short) is provided in the arguments */
    if(strstr(args,"hs"))
    {
        printf("\nrestore: restore [-h -hs]\n");
        return true;
    }

    /* Check if 'h' (help) is provided in the arguments */
    if(strstr(args,"h"))
    {
        printf("\n\
restore: restore [-h -hs]\n\
    Restores the filesystem with all directory structures and file contents.\n\n");
        return true;
    }

    /* Open the filesystem metadata file */
    const char *metadata_path = "./fs_metadata.bin";
    
    FILE *file = fopen(metadata_path, "rb");
    if (!file) {
        printf("Error: Could not open filesystem backup at %s\n", metadata_path);
        return true;
    }
    
    /* Read and verify filesystem version and magic number */
    uint32_t magic, version;
    if (fread(&magic, sizeof(uint32_t), 1, file) != 1 ||
        fread(&version, sizeof(uint32_t), 1, file) != 1 ||
        magic != 0x4653594D) {
        printf("Error: Invalid or corrupted backup file format\n");
        fclose(file);
        return true;
    }
    
    /* Clear existing filesystem */
    /* Reset root directory */
    strcpy(root.name, "root");
    root.file_count = 0;
    root.child_count = 1;
    root.parent = NULL;
    root.child[0] = &root;
    
    /* Set current directory to root */
    current_dir = &root;
    
    /* Restore the root directory */
    if (!load_directory(file, &root, 0)) {
        printf("Error: Failed to restore filesystem structure\n");
        fclose(file);
        return true;
    }
    
    fclose(file);
    printf("Filesystem restored successfully from %s\n", metadata_path);
    return false;
}

/* 
 * Recursively load a directory and all its contents
 */
bool load_directory(FILE *file, fs_Directory *parent, int depth) {
    uint8_t type;
    int i;
    
    /* Prevent extremely deep recursion */
    if (depth > 10) {
        printf("Error: Filesystem structure too deep\n");
        return false;
    }
    
    if (fread(&type, sizeof(uint8_t), 1, file) != 1 || type != 0) {
        printf("Error: Expected directory entry\n");
        return false;
    }
    
    /* Read directory name*/
    uint16_t name_len;
    char dir_name[MAX_FILENAME];
    if (fread(&name_len, sizeof(uint16_t), 1, file) != 1 || name_len >= MAX_FILENAME) {
        printf("Error: Invalid directory name length\n");
        return false;
    }
    
    if (fread(dir_name, sizeof(char), name_len, file) != name_len) {
        printf("Error: Could not read directory name\n");
        return false;
    }
    dir_name[name_len] = '\0';
    
    /* Create directory */
    fs_Directory *directory;
    if (parent == &root && strcmp(dir_name, "root") == 0) {
        /* If it's the root, use existing root */
        directory = &root;
    } else {
        /* Create new directory */
        directory = create_directory(parent, dir_name);
    }
    
    if (!directory) {
        printf("Error: Could not create directory %s\n", dir_name);
        return false;
    }
    
    /* Read child and file counts*/
    uint16_t child_count, file_count;
    if (fread(&child_count, sizeof(uint16_t), 1, file) != 1 ||
        fread(&file_count, sizeof(uint16_t), 1, file) != 1) {
        printf("Error: Could not read directory counts\n");
        return false;
    }
    
    /* Load child directories*/
    for (i = 0; i < child_count; i++) {
        if (!load_directory(file, directory, depth + 1)) {
            return false;
        }
    }
    
    /* Load files*/
    for (i = 0; i < file_count; i++) {
        if (!load_file(file, directory)) {
            return false;
        }
    }
    
    return true;
}

/*
 * Load a file and its contents
 */
bool load_file(FILE *file, fs_Directory *directory) {
    uint8_t type;
    uint16_t name_len;
    uint32_t content_len;
    
    if (fread(&type, sizeof(uint8_t), 1, file) != 1 || type != 1) {
        printf("Error: Expected file entry\n");
        return false;
    }
    
    /* Read file name*/
    if (fread(&name_len, sizeof(uint16_t), 1, file) != 1 || name_len >= MAX_FILENAME) {
        printf("Error: Invalid file name length\n");
        return false;
    }
    
    /* Verify we have space in the directory */
    if (directory->file_count >= MAX_FILES) {
        printf("Error: Maximum number of files exceeded\n");
        return false;
    }
    
    /* Add new file to directory */
    fs_File *file_obj = &directory->files[directory->file_count];
    
    if (fread(file_obj->name, sizeof(char), name_len, file) != name_len) {
        printf("Error: Could not read file name\n");
        return false;
    }
    file_obj->name[name_len] = '\0';
    
    /* Read content length*/
    if (fread(&content_len, sizeof(uint32_t), 1, file) != 1) {
        printf("Error: Could not read content length\n");
        return false;
    }
    
    /* Ensure content length doesn't exceed our buffer*/
    if (content_len > FILE_CONTENT_SIZE) {
        printf("Error: File content too large\n");
        return false;
    }
    
    /* Read file content*/
    if (content_len > 0) {
        if (fread(file_obj->content, sizeof(char), content_len, file) != content_len) {
            printf("Error: Could not read file content\n");
            return false;
        }
        file_obj->content[content_len] = '\0';
    } else {
        file_obj->content[0] = '\0';
    }
    
    /* Increment file count */
    directory->file_count++;
    
    return true;
}

/* 
 * Create a new directory and add it to parent's children 
 */
fs_Directory* create_directory(fs_Directory *parent, const char *name) {
    /* Verify we have space in the parent directory */
    if (parent->child_count >= MAX_FILES) {
        printf("Error: Maximum number of directories exceeded\n");
        return NULL;
    }
    
    /* Allocate memory for new directory */
    fs_Directory *new_dir = (fs_Directory*)malloc(sizeof(fs_Directory));
    if (!new_dir) {
        printf("Error: Memory allocation failed for new directory\n");
        return NULL;
    }
    
    /* Initialize new directory */
    strcpy(new_dir->name, name);
    new_dir->file_count = 0;
    new_dir->child_count = 1;
    new_dir->parent = parent;
    new_dir->child[0] = new_dir;  /* Self-reference */
    
    /* Add to parent's children */
    parent->child[parent->child_count] = new_dir;
    parent->child_count++;
    
    return new_dir;
}

#endif /* CMD_RESTORE_H */