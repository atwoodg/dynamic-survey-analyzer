#include <stdio.h>
#include <string.h>
#include "dyn_survey.h"
#include "emalloc.h"
#include "input_handling.h"
#include "processing.h"

/* processing.c */

void program_proportions(Strings responses, Strings categories, int index, int props[]) {
    // Initialize counts
    for (int i = 0; i < categories.size; i++) {
        props[i] = 0;
    }

    // Count occurrences of each category value in that column
    for (int j = 0; j < responses.size; j++) {
        Strings tokens = tokenize(responses.array[j], ",");
        char *value = tokens.array[index];

        for (int i = 0; i < categories.size; i++) {
            if (strcmp(value, categories.array[i]) == 0) {
                props[i]++;
                break;
            }
        }
    }
}

void question_proportions(Strings responses, Strings questions, Strings options, int proportions[questions.size][options.size]) {

    //Filling prop with 0's
    for (int i = 0; i < questions.size; i++) {
        for (int j = 0; j < options.size; j++) {
            proportions[i][j] = 0;
        }
    }

    for (int j = 0; j < responses.size; j++) { //Outer loops through lines
        Strings answers = tokenize(responses.array[j], ",");

        for (int k = 0; k < questions.size; k++) { //Inner loops through answers in line j
            char *ans = answers.array[k+2];
            for (int i = 0; i < options.size; i++) {
                if (strcmp(ans, options.array[i]) == 0) {
                    proportions[k][i] += 1;
                    break;
                }
            }
        }
    }
}

void averages(Strings responses, Strings questions, Strings options, int proportions[questions.size][options.size], double avgs[questions.size][1]) {

    for (int q = 0; q < questions.size; q++) {
        avgs[q][0] = 0;

        for (int i = 0; i < options.size; i++) {
            avgs[q][0] += proportions[q][i]*(i+1);
            //total += proportions[q][i];
        }
        avgs[q][0] = avgs[q][0]/(responses.size);
    }
}
