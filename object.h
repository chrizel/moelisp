#ifndef OBJECT_H
#define OBJECT_H

struct object;
typedef struct object * pobject;

typedef pobject (*cfunc)(pobject params);

/*
 * flags: 0000|0000
 *         ^^^|^^^^
 *          GC|Type
 *            |
 */
struct object {
    char flags;
    union {
        char *symbol;
        int character;
        double number;
        cfunc func;
        struct {
            pobject car;
            pobject cdr;
        } cons;
    } data;
};

#define NIL 0
#define T_SYMBOL    0x01
#define T_CHARACTER 0x02
#define T_NUMBER    0x03
#define T_FUNC      0x04
#define T_CONS      0x05

static inline int is_nil(pobject o) { return !o; }
static inline int is_symbol(pobject o) 
    { return o && (o->flags & 0x0f) == T_SYMBOL; }
static inline int is_character(pobject o) 
    { return o && (o->flags & 0x0f) == T_CHARACTER; }
static inline int is_number(pobject o) 
    { return o && (o->flags & 0x0f) == T_NUMBER; }
static inline int is_func(pobject o) 
    { return o && (o->flags & 0x0f) == T_FUNC; }
static inline int is_cons(pobject o) 
    { return o && (o->flags & 0x0f) == T_CONS; }

extern pobject object_new(char type);
extern void object_free(pobject o);

#endif
