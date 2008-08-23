#ifndef OBJECT_H
#define OBJECT_H

struct object;
typedef struct object * pobject;

typedef pobject (*pcfunc)(pobject env, pobject params);

/*
 * flags: 0000|0000
 *        ^^^^|^^^^
 *          GC|Type
 *            |
 */
struct object {
    char flags;
    union {
        int character;
        double number;
        pcfunc cfunc;
        struct {
            int length;
            char *value;
        } symbol;
        struct {
            pobject car;
            pobject cdr;
        } cons;
        struct {
            pobject env;
            pobject code;
        } closure;
        struct {
            pobject env;
            pobject code;
        } macro;
    } data;
};

#define NIL 0
#define T_SYMBOL    0x01
#define T_CHARACTER 0x02
#define T_NUMBER    0x03
#define T_CFUNC     0x04
#define T_CONS      0x05
#define T_CLOSURE   0x06
#define T_MACRO     0x07

int object_new_count;
int object_free_count;

pobject object_true;
pobject symbol_parent_env;

static inline int object_type(pobject o)
    { return o ? (o->flags & 0x0f) : NIL; }
static inline int is_nil(pobject o) { return !o; }
static inline pobject object_bool(int b)
    { return b ? object_true : NIL; }

static inline int is_symbol(pobject o) 
    { return object_type(o) == T_SYMBOL; }
static inline int is_character(pobject o) 
    { return object_type(o) == T_CHARACTER; }
static inline int is_number(pobject o) 
    { return object_type(o) == T_NUMBER; }
static inline int is_cfunc(pobject o) 
    { return object_type(o) == T_CFUNC; }
static inline int is_cons(pobject o) 
    { return object_type(o) == T_CONS; }
static inline int is_closure(pobject o)
    { return object_type(o) == T_CLOSURE; }
static inline int is_macro(pobject o)
    { return object_type(o) == T_MACRO; }

extern pobject object_new(char type);
extern void object_free(pobject o);
extern int object_equal(pobject o1, pobject o2);
extern pobject object_prepend_begin(pobject o);

#endif
