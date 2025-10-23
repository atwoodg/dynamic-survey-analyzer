#ifndef _OUTPUT_H_
#define _OUTPUT_H_
#include "dyn_survey.h"

/* add your include and prototypes here*/
void outputInfo(Response responses);
void output100(Response responses, Response questions, Response options, int **props);
void output010(Response responses, Response questions, Response options, int **props);
void output001(Response programs, Response residency, int prog[programs.size], int res[residency.size], int survey_size);
void output(int format, Response responses, Response questions, Response options, int **props, Response programs, Response residency, int *prog, int *res, int survey_size);

#endif
