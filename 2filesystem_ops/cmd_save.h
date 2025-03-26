#ifndef CMD_SAVE_H
#define CMD_SAVE_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <errno.h>

/* Forward declarations for recursive saving */
bool save_directory(FILE *file, fs_Directory *directory, int depth);
bool save_file(FILE *file, fs_File *file_obj);

bool fs_save(char *object, char *args) {
    /* Check if 'hs' (help short) is provided in the arguments */
    if(strstr(args,"hs"))
    {
        printf("\nsave: save [-h -hs]\n");
        return true;
    }

    /* Check if 'h' (help) is provided in the arguments */
    if(strstr(args,"h"))
    {
        printf("\n\
save: save [-h -hs]\n\
    Saves the filesystem with all directory structures and file contents.\n\n");
        return true;
    }

    /* Open the filesystem metadata file */
    const char *metadata_path = "./fs_metadata.bin";
    
    FILE *file = fopen(metadata_path, "wb");
    if (!file) {
        printf("Error: Could not save filesystem metadata to %s - %s\n", 
               metadata_path, strerror(errno));
        return true;
    }
    
    /* Write filesystem version and magic number */
    unsigned int version = 1;
    unsigned int magic = 0x4653594D; /* "FSYM" - FileSystem Magic */
    if (fwrite(&magic, sizeof(unsigned int), 1, file) != 1 ||
        fwrite(&version, sizeof(unsigned int), 1, file) != 1) {
        printf("Error: Could not write filesystem header\n");
        fclose(file);
        return true;
    }
    
    /* Save the entire directory structure recursively starting from root */
    bool success = save_directory(file, &root, 0);
    
    /* Check for any write errors before closing */
    if (ferror(file)) {
        printf("Error: Write error occurred during saving\n");
        success = false;
    }
    
    fclose(file);
    
    if (success) {
        printf("Filesystem saved successfully to %s\n", metadata_path);
        return false;  /* Return false indicating the operation was completed */
    } else {
        printf("Error occurred while saving filesystem\n");
        return true;
    }
}

/* 
 * Recursively save a directory and all its contents
 * Added depth parameter to prevent infinite recursion
 */
bool save_directory(FILE *metadata_file, fs_Directory *directory, int depth) {
    int i;
    unsigned char type;
    unsigned short name_len;
    unsigned short child_count, file_count;
    
    /* Prevent extremely deep recursion */
    if (depth > 10) {
        printf("Error: Filesystem structure too deep\n");
        return false;
    }
    
    if (!directory) return false;
    
    /* Write entry type (0 for directory) */
    type = 0;
    if (fwrite(&type, sizeof(unsigned char), 1, metadata_file) != 1) {
        printf("Error: Could not write directory type\n");
        return false;
    }
    
    /* Write directory name */
    name_len = strlen(directory->name);
    if (fwrite(&name_len, sizeof(unsigned short), 1, metadata_file) != 1 || 
        fwrite(directory->name, sizeof(char), name_len, metadata_file) != name_len) {
        printf("Error: Could not write directory name\n");
        return false;
    }
    
    /* Write counts (excluding self-reference) */
    child_count = directory->child_count > 1 ? directory->child_count - 1 : 0;
    file_count = directory->file_count;
    if (fwrite(&child_count, sizeof(unsigned short), 1, metadata_file) != 1 ||
        fwrite(&file_count, sizeof(unsigned short), 1, metadata_file) != 1) {
        printf("Error: Could not write directory counts\n");
        return false;
    }
    
    /* Save child directories recursively (skip self-reference) */
    for (i = 1; i < directory->child_count; i++) {
        if (!save_directory(metadata_file, directory->child[i], depth + 1)) {
            return false;
        }
    }
    
    /* Save files in this directory */
    for (i = 0; i < directory->file_count; i++) {
        if (!save_file(metadata_file, &directory->files[i])) {
            return false;
        }
    }
    
    return true;
}

/*
 * Save a file and its contents
 */
bool save_file(FILE *metadata_file, fs_File *file_obj) {
    unsigned char type;
    unsigned short name_len;
    unsigned int content_len = 0;
    
    if (!file_obj) return false;
    
    /* Write entry type (1 for file) */
    type = 1;
    if (fwrite(&type, sizeof(unsigned char), 1, metadata_file) != 1) {
        printf("Error: Could not write file type\n");
        return false;
    }
    
    /* Write file name */
    name_len = strlen(file_obj->name);
    if (fwrite(&name_len, sizeof(unsigned short), 1, metadata_file) != 1 || 
        fwrite(file_obj->name, sizeof(char), name_len, metadata_file) != name_len) {
        printf("Error: Could not write file name\n");
        return false;
    }
    
    /* Calculate content length */
    while (content_len < sizeof(file_obj->content) && 
           file_obj->content[content_len] != '\0') {
        content_len++;
    }
    
    /* Write content length */
    if (fwrite(&content_len, sizeof(unsigned int), 1, metadata_file) != 1) {
        printf("Error: Could not write file content length\n");
        return false;
    }
    
    /* Write file content if any */
    if (content_len > 0) {
        if (fwrite(file_obj->content, sizeof(char), content_len, metadata_file) != content_len) {
            printf("Error: Could not write file content\n");
            return false;
        }
    }
    
    return true;
}

#endif /* CMD_SAVE_H */