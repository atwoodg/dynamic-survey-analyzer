#ifndef _PROCESSING_H_
#define _PROCESSING_H_
#include "dyn_survey.h"
/* add your include and prototypes here*/

void program_proportions(Response responses, Response categories, int index, int props[]);
void question_proportions(Response responses, Response questions, Response options, int **proportions);
void averages(Response responses, Response questions, Response options, int **proportions, double **avgs);

#endif
