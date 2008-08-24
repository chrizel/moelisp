#ifndef EVAL_H
#define EVAL_H

#include "object.h"

extern pobject eval(pobject env, pobject code);
extern pobject eval_apply(pobject env, pobject proc, pobject params);

#endif
