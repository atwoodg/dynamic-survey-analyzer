#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 50
#define MAX_CHARS 2000

typedef struct {
    char array[MAX_LINES][MAX_CHARS];
    int size;
} Strings;

//Function to determine the format of the output based on first line giving 0 or 1 combination
int format(char lines[][MAX_CHARS]) {

    //Setting variables to tokenize by comma
    char delimiter[] = ",";
    char fmt[3] = {0,0,0};
    char *token = strtok(lines[0], delimiter);

    //putting integer values into own array spots
    for (int i = 0; i < 3 && token; i++) {
        fmt[i] = atoi(token);
        token = strtok(NULL, delimiter);
    }

    //Finding format
    if (fmt[0] == 1 && fmt[1] == 0 && fmt[2] == 0) return 1;
    else if (fmt[0] == 0 && fmt[1] == 1 && fmt[2] == 0) return 2;
    else if (fmt[0] == 0 && fmt[1] == 0 && fmt[2] == 1) return 3;
    else if (fmt[0] == 1 && fmt[1] == 1 && fmt[2] == 0) return 4;
    else if (fmt[0] == 0 && fmt[1] == 1 && fmt[2] == 1) return 5;
    else if (fmt[0] == 1 && fmt[1] == 0 && fmt[2] == 1) return 6;
    else return 7;
}

//Function to tokenize any line into 2D array using specified delimeter
Strings tokenize(char *line, char delimeter[]) {
    Strings tokenized;
    tokenized.size = 0;
    char* token;

    token = strtok(line, delimeter);
    while (token != NULL) {
        while (*token == ' ') token++;
        strcpy(tokenized.array[tokenized.size], token);
        token = strtok(NULL, delimeter);
        tokenized.size++;
    }

    return tokenized;
}

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
        int total = 0;

        for (int i = 0; i < options.size; i++) {
            avgs[q][0] += proportions[q][i]*(i+1);
            //total += proportions[q][i];
        }
        avgs[q][0] = avgs[q][0]/(responses.size);
    }
}

void outputInfo(Strings responses) {

    printf("ECS Student Survey\n");
    printf("SURVEY RESPONSE STATISTICS\n\n");
    printf("NUMBER OF RESPONDENTS: %d\n\n", responses.size);

}

void output100(Strings responses, Strings questions, Strings options, int props[questions.size][options.size]) {

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

void output010(Strings responses, Strings questions, Strings options, int props[questions.size][options.size]) {
    double avgs[questions.size][1];
    averages(responses, questions, options, props, avgs);

    printf("#####\n");
    printf("FOR EACH QUESTION/ASSERTION BELOW, THE AVERAGE RESPONSE IS SHOWN (FROM 1-DISAGREEMENT TO 4-AGREEMENT)\n\n");

    for (int q = 0; q < questions.size; q++) {
        printf("%d. %s - %.2f\n", q + 1, questions.array[q], avgs[q][0]);
    }
    printf("\n");
}

void output001(Strings programs, Strings residency, int prog[programs.size], int res[residency.size]) {
    printf("#####\n");
    printf("FOR EACH DEMOGRAPHIC CATEGORY BELOW, RELATIVE FREQUENCIES ARE COMPUTED FOR EACH ATTRIBUTE VALUE\n\n");
    printf("UNDERGRADUATE PROGRAM\n");

    for (int d = 0; d < programs.size; d++) {
        double num = (double) prog[d]*10;
        printf("%.2f: %s\n", num, programs.array[d]);
    }

    printf("\nRESIDENCE STATUS \n");

    for (int r = 0; r < residency.size; r++) {
        double num = (double) res[r]*10;
        printf("%.2f: %s\n", num, residency.array[r]);
    }


}

int main() {
    //Inititalizing buffer for max strings
    char buffer[MAX_CHARS];
    char lines[MAX_LINES][MAX_CHARS];
    int i = 0;

    //while loop that gets each line in file and c>
    while (fgets(buffer, MAX_CHARS, stdin) != NULL){
        if (buffer[0] != '#') {
            buffer[strcspn(buffer, "\n")] = 0;
            strcpy(lines[i], buffer);
            i += 1;
        }
    }

    //Format of output
    int output = format(lines);

    //Reading in questions/assertions
    Strings programs = tokenize(lines[1], ",");
    Strings residency = tokenize(lines[2], ",");
    Strings questions = tokenize(lines[3], ";");
    Strings options = tokenize(lines[4], ",");
    int survey_size = atoi(lines[5]);

    Strings responses;
    responses.size = 0;
    for (int i = 6; i < survey_size + 6; i++) {
        strcpy(responses.array[responses.size++], lines[i]);
    }

    int props[questions.size][options.size];
    question_proportions(responses, questions, options, props);

    int program_props[programs.size];
    int residency_props[residency.size];

    program_proportions(responses, programs, 0, program_props);
    program_proportions(responses, residency, 1, residency_props);

    //Output
    if (output == 1) {
        outputInfo(responses);
        output100(responses, questions, options, props);
    }
    if (output == 2) {
        outputInfo(responses);
        output010(responses, questions, options, props);
    }
    if (output == 4) {
        outputInfo(responses);
        output100(responses, questions, options, props);
        output010(responses, questions, options, props);
    }
    if (output==3) {
        outputInfo(responses);
        output001(programs, residency, program_props, residency_props);
    }
    if (output == 7) {
        outputInfo(responses);
        output100(responses, questions, options, props);
        output010(responses, questions, options, props);
        output001(programs, residency, program_props, residency_props);
    }


    return 0;
}
