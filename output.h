#ifndef _OUTPUT_H_
#define _OUTPUT_H_
#include "dyn_survey.h"

/* add your include and prototypes here*/
void outputInfo(Strings responses);
void output100(Strings responses, Strings questions, Strings options, int props[questions.size][options.size]);
void output010(Strings responses, Strings questions, Strings options, int props[questions.size][options.size]);
void output001(Strings programs, Strings residency, int prog[programs.size], int res[residency.size]);
void output(int format, Strings responses, Strings questions, Strings options, int props[questions.size][options.size], Strings programs, Strings residency, int prog[programs.size], int res[residency.size]);

#endif
