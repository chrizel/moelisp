#ifndef MACRO_H
#define MACRO_H

#include "object.h"

extern pobject macro_new(pobject env, pobject params, pobject code);
extern pobject macro_expand(pobject call_env, pobject macro, pobject params);
extern pobject macro_eval(pobject call_env, pobject macro, pobject params);

#endif
