#include <stdio.h>
#include "dyn_survey.h"
#include "processing.h"
#include "output.h"
/* output.c */

void outputInfo(Response responses) {

    printf("ECS Student Survey\n");
    printf("SURVEY RESPONSE STATISTICS\n\n");
    printf("NUMBER OF RESPONDENTS: %d\n\n", responses.size);

}

void output100(Response responses, Response questions, Response options, int **props) {

    printf("#####\n");
    printf("FOR EACH QUESTION/ASSERTION BELOW, RELATIVE PERCENTUAL FREQUENCIES ARE COMPUTED FOR EACH LEVEL OF AGREEMENT\n\n");

    for (int q = 0; q < questions.size; q++) {
        printf("%d. %s\n", q + 1, questions.array[q]);
        for (int o = 0; o < options.size; o++) {
            double pct = ((double) props[q][o] / responses.size) * 100.0;
            printf("%.2f: %s\n", pct, options.array[o]);
        }
        printf("\n");
    }
}

void output010(Response responses, Response questions, Response options, int **props) {
    double avgs[questions.size][1];
    averages(responses, questions, options, props, avgs);

    printf("#####\n");
    printf("FOR EACH QUESTION/ASSERTION BELOW, THE AVERAGE RESPONSE IS SHOWN (FROM 1-DISAGREEMENT TO 4-AGREEMENT)\n\n");

    for (int q = 0; q < questions.size; q++) {
        printf("%d. %s - %.2f\n", q + 1, questions.array[q], avgs[q][0]);
    }
    printf("\n");
}

void output001(Response programs, Response residency, int prog[programs.size], int res[residency.size], int survey_size) {
    printf("#####\n");
    printf("FOR EACH DEMOGRAPHIC CATEGORY BELOW, RELATIVE FREQUENCIES ARE COMPUTED FOR EACH ATTRIBUTE VALUE\n\n");
    printf("UNDERGRADUATE PROGRAM\n");

    for (int d = 0; d < programs.size; d++) {
        double num = ((double) prog[d] / survey_size) * 100.0;
        printf("%.2f: %s\n", num, programs.array[d]);
    }

    printf("\nRESIDENCE STATUS \n");

    for (int r = 0; r < residency.size; r++) {
        double num = ((double) res[r] / survey_size) * 100.0;;
        printf("%.2f: %s\n", num, residency.array[r]);
    }
}

void output(int format, Response responses, Response questions, Response options, int **props, Response programs, Response residency, int *prog, int *res, int survey_size) {
    switch (format) {
        case 1:
            outputInfo(responses);
            output100(responses, questions, options, props);
            break;
        case 2:
            outputInfo(responses);
            output010(responses, questions, options, props);
            break;
        case 3:
            outputInfo(responses);
            output001(programs, residency, prog, res, survey_size);
            break;
        case 4:
            outputInfo(responses);
            output010(responses, questions, options, props);
            output001(programs, residency, prog, res, survey_size);
            break;
        case 5:
            outputInfo(responses);
            output100(responses, questions, options, props);
            output001(programs, residency, prog, res, survey_size);
            break;
        case 6:
            outputInfo(responses);
            output100(responses, questions, options, props);
            output010(responses, questions, options, props);
            break;
        case 7:
            outputInfo(responses);
            output100(responses, questions, options, props);
            output010(responses, questions, options, props);
            output001(programs, residency, prog, res, survey_size);
            break;
    }
}
