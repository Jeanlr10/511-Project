#include <ncurses.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CONTENT 1024

bool fs_edit(char object[],char args[], fs_Directory *workingdir) {
    int i;
    fs_File *editfile = NULL;

    /* Find the file in the directory*/
    for (i = 0; i < workingdir->file_count; i++) {
        if (strcmp(workingdir->files[i].name, object) == 0) {
            editfile = &workingdir->files[i];
            break;
        }
    }
    
    if (!editfile) {
        printf("File Not Found"); /* File not found*/
        return true;  
    }

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int pos = strlen(editfile->content);
    int ch;

    while (1) {
        clear();
        mvprintw(0, 0, "Editing file: %s (Press ESC to save and exit)", object);
        mvprintw(2, 0, "%s", editfile->content);
        move(2, pos);
        refresh();

        ch = getch();

        if (ch == 27) { /* ESC key to exit*/
            break;
        } else if (ch == KEY_LEFT && pos > 0) {
            pos--;
        } else if (ch == KEY_RIGHT && pos < strlen(editfile->content)) {
            pos++;
        } else if ((ch == KEY_BACKSPACE || ch == 127) && pos > 0) {
            memmove(&editfile->content[pos - 1], &editfile->content[pos], strlen(editfile->content) - pos + 1);
            pos--;
        } else if (isprint(ch) && strlen(editfile->content) < MAX_CONTENT - 1) {
            memmove(&editfile->content[pos + 1], &editfile->content[pos], strlen(editfile->content) - pos + 1);
            editfile->content[pos] = ch;
            pos++;
        }
    }

    endwin();
    return true;
}
