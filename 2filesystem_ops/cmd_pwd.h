#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* Function to print the current working directory */
bool fs_pwd(char object[], char args[], fs_Directory *workingdir) {
    /* Check if the user requested the 'hs' flag for a short help message */
    if (strstr(args, "hs")) {
        printf("\npwd: pwd [-h -hs]\n");  /* Print basic usage for 'pwd' command */
        return true;  /* Return true to indicate help was shown */
    }

    /* Check if the user requested the '-h' flag for a detailed help message */
    if (strstr(args, "h")) {
        printf("\n\
pwd: pwd [-h -hs]\n\
    Returns the current directory.\n\n");  /* Print detailed help message for 'pwd' command */
        return true;  /* Return true to indicate help was shown */
    }

    /* Print the current working directory */
    printf("%s\n", workingdir);  /* Here, printing workingdir directly will not work as expected since it's a pointer. You likely need to print a specific attribute of 'workingdir' (e.g., workingdir->name) */
    return true;  /* Return true to indicate the operation was successful */
}
