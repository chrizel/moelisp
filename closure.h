#ifndef CLOSURE_H
#define CLOSURE_H

#include "object.h"

extern pobject closure_new(pobject env, pobject params, pobject code);
extern pobject closure_eval(pobject call_env, pobject closure, pobject params, int eval_params);

#endif
