/* input_handling.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "emalloc.h"
#include "dyn_survey.h"
#include "input_handling.h"

//Function to determine the format of the output based on first line giving 0 or 1 combination
int format(Response lines) {

    //Setting variables to tokenize by comma
    char delimiter[] = ",";
    int fmt[3] = {0,0,0};
    char *copy = emalloc(strlen(lines.array[0])+1);
    strcpy(copy, lines.array[0]);
    char *token = strtok(copy, delimiter);

    //putting integer values into own array spots
    for (int i = 0; i < 3 && token; i++) {
        fmt[i] = atoi(token);
        token = strtok(NULL, delimiter);
    }
    //Finding format
    if (fmt[0] == 1 && fmt[1] == 0 && fmt[2] == 0) return 1;
    else if (fmt[0] == 0 && fmt[1] == 1 && fmt[2] == 0) return 2;
    else if (fmt[0] == 0 && fmt[1] == 0 && fmt[2] == 1) return 3;
    else if (fmt[0] == 0 && fmt[1] == 1 && fmt[2] == 1) return 4;
    else if (fmt[0] == 1 && fmt[1] == 0 && fmt[2] == 1) return 5;
    else if (fmt[0] == 1 && fmt[1] == 1 && fmt[2] == 0) return 6;
    else if (fmt[0] == 1 && fmt[1] == 1 && fmt[2] == 1) return 7;
    free(copy);
    return 0;
}

//Function to tokenize any line into 2D array using specified delimeter
Response tokenize(char *line, char delimeter[]) {
    Response tokenized;
    tokenized.array = NULL;
    tokenized.size = 0;
    char *lines = emalloc(strlen(line)+1);
    strcpy(lines, line);
    char *token = strtok(lines, delimeter);
    while (token != NULL) {
        while (*token == ' ') token++;
        tokenized.array = erealloc(tokenized.array, (tokenized.size + 1) * sizeof(char *));
        tokenized.array[tokenized.size] = emalloc(strlen(token) + 1);
        strcpy(tokenized.array[tokenized.size], token);
        tokenized.size++;
        token = strtok(NULL, delimeter);
    }
    free(lines);
    return tokenized;
}
