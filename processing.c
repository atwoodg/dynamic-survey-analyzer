#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dyn_survey.h"
#include "emalloc.h"
#include "input_handling.h"
#include "processing.h"

/* processing.c */

//computes the proportions array for students programs and residencies for output
void program_proportions(Response responses, Response categories, int index, int props[]) {
    // Initialize counts
    for (int i = 0; i < categories.size; i++) {
        props[i] = 0;
    }

    // Count occurrences of each category value in that column
    for (int j = 0; j < responses.size; j++) {
        Response tokens = tokenize(responses.array[j], ",");
        char *value = tokens.array[index];

        for (int i = 0; i < categories.size; i++) {
            if (strcmp(value, categories.array[i]) == 0) {
                props[i]++;
                break;
            }
        }
        for (int k = 0; k < tokens.size; k++) {
            free(tokens.array[k]);
        }
        free(tokens.array);
    }
}

//computes proporitons for questions and their answers
void question_proportions(Response responses, Response questions, Response options, int **proportions) {

    //Filling prop with 0's
    for (int i = 0; i < questions.size; i++) {
        for (int j = 0; j < options.size; j++) {
            proportions[i][j] = 0;
        }
    }

    for (int j = 0; j < responses.size; j++) { //Outer loops through lines
        Response answers = tokenize(responses.array[j], ",");

        for (int k = 0; k < questions.size; k++) { //Inner loops through answers in line j
            char *ans = answers.array[k+2];
            for (int i = 0; i < options.size; i++) {
                if (strcmp(ans, options.array[i]) == 0) {
                    proportions[k][i] += 1;
                    break;
                }
            }
        }
        for (int k = 0; k < answers.size; k++) {
            free(answers.array[k]);
        }
        free(answers.array);
    }
}


void averages(Response responses, Response questions, Response options, int **proportions, double **avgs) {
    //filling averages with 0's and computing
    for (int q = 0; q < questions.size; q++) {
        avgs[q][0] = 0;

        for (int i = 0; i < options.size; i++) {
            avgs[q][0] += proportions[q][i]*(i+1);
        }
        avgs[q][0] = avgs[q][0]/(responses.size);
    }
}
