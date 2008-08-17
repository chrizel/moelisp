#ifndef ENV_H
#define ENV_H

extern pobject env_define(pobject env, pobject symbol, pobject value);
extern pobject env_lookup(pobject env, pobject symbol);

#endif
