#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#define VECT_LEN 20
/* This is the array of available functions, each is associated with a 
 * command line option. When adding functions do it at the end of the 
 * array, so not to break the already defined command line arguments */
int (*fun[])(int) = {
    isprint,
    isalnum,
    isalpha,
    isascii,
    isblank,
    iscntrl,
    isdigit,
    isgraph,
    islower,
    isupper,
    ispunct,
    isspace,
    isxdigit,
};

int main(int argc, char ** argv) {
    /* this array gets populated with the selected functions */
    int (*function_vector[VECT_LEN])(int);

    int ch;
    /* read characters on at a time. possibly it could be made more efficient
     * by buffering */
    while ((ch = getchar()) != EOF) {
        if (execute_loop(ch, function_vector)) {
            putchar(ch);
        }
    }

    return 0;
}

int execute_loop(int character, int * function_vector[](*)) {
    int result = 0;
    for(int i = 0; function_vector[i] != NULL; i++) {
        result = function_vector[i](character);
        if (result != 0) break;
    } 
}
