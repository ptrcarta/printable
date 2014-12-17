#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#define VECT_LEN 20
int main() {
    
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
    int (*function_vector[VECT_LEN])(int);
   



    int ch;
    while ((ch = getchar()) != EOF) {
        if (fun(ch)) {
            putchar(ch);
        }
    }

    return 0;
}

int execute_loop(int character, int * function_vector[]) {
    int result = 0;
    for(int i = 0; function_vector[i] != NULL; i++) {
        result = function_vector[i](character);
        if (result != 0) break;
    } 
}
