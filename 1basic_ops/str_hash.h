#include <math.h>

/* Function to generate a hash value for a string */
int strhash(char string[]) {
    int final = 0;  /* Initialize final hash value to 0 */
    int i;

    /* Loop through the string from end to start */
    for (i = strlen(string); i > 0; i--) {
        /* Update the hash value by adding the current character's numeric value (minus '0') multiplied by a power of 5 */
        final += (string[i] - '0') * pow(5, strlen(string) - i);
    }

    return final;  /* Return the final computed hash value */
}
