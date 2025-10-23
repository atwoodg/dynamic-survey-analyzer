#ifndef _PROCESSING_H_
#define _PROCESSING_H_
#include "dyn_survey.h"
/* add your include and prototypes here*/

void program_proportions(Strings responses, Strings categories, int index, int props[]);
void question_proportions(Strings responses, Strings questions, Strings options, int proportions[questions.size][options.size]);
void averages(Strings responses, Strings questions, Strings options, int proportions[questions.size][options.size], double avgs[questions.size][1]);


#endif
