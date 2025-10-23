#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dyn_survey.h"
#include "emalloc.h"
#include "input_handling.h"
#include "processing.h"
#include "output.h"

int main() {
    //Inititalizing buffer for max strings
    char buffer[1000];
    Response lines = {NULL, 0};

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (buffer[0] != '#') {
            buffer[strcspn(buffer, "\n")] = 0;
            lines.array = erealloc(lines.array, (lines.size + 1) * sizeof(char *));
            lines.array[lines.size] = emalloc(strlen(buffer) + 1);
            strcpy(lines.array[lines.size], buffer);
            lines.size++;
        }
    }

    //Format of output
    int fmt = format(lines);

    //Reading in questions/assertions
    Response programs = tokenize(lines.array[1], ",");
    Response residency = tokenize(lines.array[2], ",");
    Response questions = tokenize(lines.array[3], ";");
    Response options = tokenize(lines.array[4], ",");
    int survey_size = atoi(lines.array[5]);

    Response responses;
    responses.array = NULL;
    responses.size = 0;
    for (int i = 6; i < survey_size + 6; i++) {
        responses.array = erealloc(responses.array, (responses.size + 1) * sizeof(char *));
        responses.array[responses.size] = emalloc(strlen(lines.array[i]) + 1);
        strcpy(responses.array[responses.size], lines.array[i]);
        responses.size++;
    }

    int **props = emalloc(questions.size * sizeof(int*));
    for (int i = 0; i < questions.size; i++) {
        props[i] = emalloc(options.size * sizeof(int));
    }
    question_proportions(responses, questions, options, props);

    int *program_props = emalloc(programs.size * sizeof(int));
    int *residency_props = emalloc(residency.size * sizeof(int));

    program_proportions(responses, programs, 0, program_props);
    program_proportions(responses, residency, 1, residency_props);

    output(fmt, responses, questions, options, props, programs, residency, program_props, residency_props, survey_size);

    for (int i = 0; i < questions.size; i++) {
        free(props[i]);
    }
    free(props);
    free(residency_props);
    free(program_props);

    return 0;
}
