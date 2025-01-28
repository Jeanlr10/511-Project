#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME 50

typedef struct {
    char name[MAX_FILENAME];
    char content[1024]; 
} File;

typedef struct {
    char name[MAX_FILENAME];
    File files[MAX_FILES]; 
    int file_count;        
} Directory;

Directory root;


void help(){
    printf("Commands:\n");
    printf("help - Display this help message\n");
    printf("quit - Exit the filesystem shell\n");
    printf("create <filename> - Create a new file\n");
    printf("delete <filename> - Delete a file\n");
    printf("save - Save the filesystem\n");
}


void quit(){
    exit(0);
}


void fs_init(){
   FILE *file = fopen("filesystem_state.dat", "r");
    if (file) {
        fread(&root, sizeof(Directory), 1, file);
        fclose(file);
        printf("Filesystem loaded successfully.\n");
    } else {
        strcpy(root.name, "root");
        root.file_count = 0;
        printf("New filesystem initialized.\n");

        FILE *new_file = fopen("filesystem_state.dat", "w");
        if (new_file) {
            fwrite(&root, sizeof(Directory), 1, new_file);
            fclose(new_file);
            printf("Filesystem saved for the first time.\n");
        } else {
            printf("Error: Unable to create filesystem file.\n");
        }
    }
}


void fs_create(const char *filename) {
    if (filename == NULL || strlen(filename) == 0) {
        printf("Error: Invalid filename.\n");
        return;
    }
    for (int i = 0; i < root.file_count; i++) {
        if (strcmp(root.files[i].name, filename) == 0) {
            printf("Error: File '%s' already exists.\n", filename);
            return;
        }
    }
    if (root.file_count >= MAX_FILES) {
        printf("Error: Maximum file limit reached.\n");
        return;
    }
    strcpy(root.files[root.file_count].name, filename);
    root.files[root.file_count].content[0] = '\0'; 
    root.file_count++;

    printf("File '%s' created successfully.\n", filename);
}



void fs_delete(const char *filename) {
    if (filename == NULL || strlen(filename) == 0) {
        printf("Error: Invalid filename.\n");
        return;
    }
    int file_index = -1;
    for (int i = 0; i < root.file_count; i++) {
        if (strcmp(root.files[i].name, filename) == 0) {
            file_index = i;
            break;
        }
    }
    if (file_index == -1) {
        printf("Error: File '%s' not found.\n", filename);
        return;
    }
    for (int i = file_index; i < root.file_count - 1; i++) {
        root.files[i] = root.files[i + 1];
    }
    root.file_count--;
    printf("File '%s' deleted successfully.\n");
}


void fs_save() {
    FILE *file = fopen("filesystem_state.txt", "w");
    if (!file) {
        printf("Error: Could not save filesystem.\n");
        return;
    }

    fprintf(file, "Directory: %s\n", root.name);
    for (int i = 0; i < root.file_count; i++) {
        fprintf(file, "File: %s\n", root.files[i].name);
    }

    fclose(file);
    printf("Filesystem saved successfully.\n");
}


int main(){
    char cmd[100];
    char arg[100];
    char *p;
    fs_init();
    printf("Welcome to the Filesystem Shell! Type 'help' for commands.\n");
    while(1){
        printf("> ");
        fgets(cmd, 100, stdin);
        p = strchr(cmd, '\n');
        
        if(p) *p = 0;
        if(strcmp(cmd, "help") == 0){
            help();
        } else if(strcmp(cmd, "quit") == 0){
            fs_save();
            printf("Exiting shell. Goodbye!\n");
            break;
        } else if(strncmp(cmd, "create", 6) == 0){
            if (sscanf(cmd, "%*s %s", arg) == 1) {
                fs_create(arg); // Create the file if an argument is provided
            } else {
                 printf("Error: No filename provided for creation.\n");
            }
        } else if (strncmp(cmd, "delete", 6) == 0) {
            sscanf(cmd, "%*s %s", arg);
            fs_delete(arg);
        } else if(strncmp(cmd, "save", 4) == 0){
            sscanf(cmd, "%*s %s", arg);
            fs_save(arg);
        } else {
            printf("Unknown command\n");
        }
    }
    return 0;
}

