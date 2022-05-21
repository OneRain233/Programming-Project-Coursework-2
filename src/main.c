//
// Created by onerain233 on 4/24/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/routeFinding.h"
#include "interface.h"


/* int main(int argc, char *argv[])
 * --------------------------------
 * This is the main function of the program.
 *
 * Parameters:
 *
 *  argc: The number of arguments passed to the program.
 *  argv: The arguments passed to the program.
 *
 *  Returns: 0 on success, -1 on failure.
 */
int main(int argc, char *argv[]) {
    char *filename = "bin/Final_Map.map";
    if (argc == 1) {
        fprintf(stdout, "Use default file: bin/Final_Map.map\n");
    } else if (argc == 2) {
        filename = argv[1];
    } else {
        fprintf(stderr, "Usage: ./RouteFinding <filename>\n");
        exit(1);
    }
    FILE *check = fopen(filename, "r");
    if (check == NULL) {
        fprintf(stderr, "File \"%s\" Not found\n", filename);
        exit(1);
    }

    dijInit(filename);
    readNode(filename);
    readLink(filename);

    promptInput();
    return 0;
}