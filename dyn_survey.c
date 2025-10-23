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
    Strings lines = {NULL, 0};

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
    Strings programs = tokenize(lines.array[1], ",");
    Strings residency = tokenize(lines.array[2], ",");
    Strings questions = tokenize(lines.array[3], ";");
    Strings options = tokenize(lines.array[4], ",");
    int survey_size = atoi(lines.array[5]);

    Strings responses;
    responses.array = NULL;
    responses.size = 0;
    for (int i = 6; i < survey_size + 6; i++) {
        responses.array = erealloc(responses.array, (responses.size + 1) * sizeof(char *));
        responses.array[responses.size] = emalloc(strlen(lines.array[i]) + 1);
        strcpy(responses.array[responses.size], lines.array[i]);
        responses.size++;
    }

    int props[questions.size][options.size];
    question_proportions(responses, questions, options, props);

    int program_props[programs.size];
    int residency_props[residency.size];

    program_proportions(responses, programs, 0, program_props);
    program_proportions(responses, residency, 1, residency_props);

    //Output
    output(fmt, responses, questions, options, props, programs, residency, program_props, residency_props);

    return 0;
}
