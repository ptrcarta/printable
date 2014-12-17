#include "printable.h"
#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>
#include <ctype.h>
#define VECT_LEN 20

/* This is the array of available functions, each is associated with a 
 * command line option. When adding functions do it at the end of the 
 * array, so not to break the already defined command line arguments */
int (*fun[])(int) = {
    isprint, /* Index:0  printable char */
    isalnum, /* Index:1  alphanum char  */
    isalpha, /* Index:2  letter         */
    isascii, /* Index:3  ascii char     */
    isblank, /* Index:4  tab or space   */
    iscntrl, /* Index:5  control char   */
    isdigit, /* Index:6  digit          */
    isgraph, /* Index:7  graphical char */
    islower, /* Index:8  lowercase alph */
    isupper, /* Index:9  uppercase aplh */
    ispunct, /* Index:10 punct char     */
    isspace, /* Index:11 any space      */
    isxdigit,/* Index:12 hex digit      */
};

int print_help() {
    return printf("Help");
}          

/* Insert the function point fun in the function pointers vector 
 * function_vector and make the last slot point to NULL */
void populate_vector(int (*fun)(int), int (*function_vector[])(int)) {
    static int index = 0;
    function_vector[index++] = fun;
    function_vector[index] = NULL;
    return;
    }

int main(int argc, char ** argv) {
    /* this array gets populated with the selected functions */
    int (*function_vector[VECT_LEN])(int) = {NULL};
    int c;

    while (1)
    {
    static struct option long_options[] = {
            {"printable",   no_argument,    NULL, 'p'},
            {"alphanum",    no_argument,    NULL, 'a'},
            {"ascii",       no_argument,    NULL, 'A'},
            {"letter",      no_argument,    NULL, 'L'},
            {"blank",       no_argument,    NULL, 'b'},
            {"control",     no_argument,    NULL, 'c'},
            {"digit",       no_argument,    NULL, 'd'},
            {"graph",       no_argument,    NULL, 'g'},
            {"lower",       no_argument,    NULL, 'l'},
            {"upper",       no_argument,    NULL, 'U'},
            {"punct",       no_argument,    NULL, 'P'},
            {"space",       no_argument,    NULL, 's'},
            {"hex",         no_argument,    NULL, 'x'},
            {"help",        no_argument,    NULL, 'h'},
            {0, 0, 0, 0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "paALbcdglUPsxh",
                       long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1) {
            break;
        }

        switch (c) {
            case 'p':
            populate_vector(fun[0], function_vector);       
            break;

            case 'A':
            populate_vector(fun[3], function_vector);       
            break;

            case 'a':
            populate_vector(fun[1], function_vector);       
            break;

            case 'L':
            populate_vector(fun[2], function_vector);       
            break;

            case 'b':
            populate_vector(fun[4], function_vector);       
            break;

            case 'c':
            populate_vector(fun[5], function_vector);       
            break;

            case 'd':
            populate_vector(fun[6], function_vector);       
            break;

            case 'g':
            populate_vector(fun[7], function_vector);       
            break;

            case 'l':
            populate_vector(fun[8], function_vector);       
            break;

            case 'U':
            populate_vector(fun[9], function_vector);       
            break;

            case 'P':
            populate_vector(fun[10], function_vector);       
            break;

            case 's':
            populate_vector(fun[11], function_vector);       
            break;

            case 'x':
            populate_vector(fun[12], function_vector);       
            break;

            case 'h':
            print_help();       
            exit(0);
            break;

            case '?':
              /* getopt_long already printed an error message. */
            abort();
            break;

            default:
            fprintf(stderr, "error: Option %c not handled correctly\n", c);
        }
    }


    if ( function_vector[0] == NULL ) {
            populate_vector(fun[0], function_vector);
    }

    /* read characters on at a time. possibly it could be made more efficient
     * by buffering */
    int ch;
    while ((ch = getchar()) != EOF) {
        if (execute_loop(ch, function_vector)) {
            putchar(ch);
        }
    }

    return 0;
}

/* Given a character it will pass it through the functions in the vector
 * and return the first non 0 value, or 0 if there isn't one */
int execute_loop(int character, int (*function_vector[])(int)) {
    int result = 0;
    for(int i = 0; function_vector[i] != NULL; i++) {
        result = function_vector[i](character);
        if (result != 0) break;
    } 
    return result;
}
