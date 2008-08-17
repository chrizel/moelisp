#include <ctype.h>
#include <stdio.h>

#include "cons.h"
#include "number.h"
#include "object.h"
#include "read.h"
#include "symbol.h"

#define TK_EOF           0
#define TK_PAREN_OPEN    1
#define TK_PAREN_CLOSE   2
#define TK_SYMBOL        3
#define TK_NUMBER        4
#define TK_DOT           5

static inline int is_symbol_char(int c)
{
    return (c >= 'a' && c <= 'z')
        || (c >= 'A' && c <= 'Z')
        || (c >= '0' && c <= '9')
        || (c == '-')
        || (c == '_')
        || (c == '*')
        || (c == '/')
        || (c == '+')
        || (c == '?')
        || (c == '#')
        || (c == '=')
        || (c == '!')
        || (c == '.')
        || (c == '>')
        || (c == '<');
}

static int skip_spaces(char *code, int *pos)
{
    int start = *pos;
    for (;code[*pos] && isspace(code[*pos]); ++(*pos))
        ;
    return *pos != start;
}

static int skip_comments(char *code, int *pos)
{
    int start = *pos;
    while (code[*pos] && (code[*pos] == ';'))
        while (code[*pos] && (code[(*pos)++] != '\n'))
            ;
    return *pos != start;
}

static int next_token(char *code, int *start, int *end)
{
    int c;

    *start = *end;
    while (code[*start] && (skip_spaces(code, start) || skip_comments(code, start)))
        ;

    *end = *start + 1;
    c = code[*start];
    if (c == '(')
        return TK_PAREN_OPEN;
    else if (c == ')')
        return TK_PAREN_CLOSE;
    else if (c == '.')
        return TK_DOT;
    else if (c >= '0' && c <= '9') {
        while (code[*end] && ((code[*end] >= '0' && code[*end] <= '9') || (code[*end] == '.')))
            ++(*end);
        return TK_NUMBER;
    } else if (is_symbol_char(c)) {
        while (code[*end] && is_symbol_char(code[*end]))
            ++(*end);
        return TK_SYMBOL;
    } else {
        return TK_EOF;
    }
}

#define moe_read_stack_macro(stack, object) { \
    pobject tmp = (object); \
    if (is_nil(stack)) \
        return tmp; \
    else if (dot_next) { \
        cons_list_last_cdr_set( &(stack->data.cons.car), tmp); \
        dot_next = 0; \
    } else { \
        cons_list_append( &(stack->data.cons.car), tmp ); \
    } \
}

pobject read(char *code)
{
    int type, start, end = 0, dot_next = 0;
    pobject stack = NIL;

    while ((type = next_token(code, &start, &end))) {
        switch (type) {
        case TK_SYMBOL:
            moe_read_stack_macro(stack, symbol_intern_by_slice(code, start, end));
            break;
        case TK_NUMBER:
            moe_read_stack_macro(stack, number_new_by_slice(code, start, end));
            break;
        case TK_PAREN_OPEN:
            cons_stack_push(&stack, NIL);
            break;
        case TK_PAREN_CLOSE:
            moe_read_stack_macro(stack, cons_stack_pop(&stack));
            break;
        case TK_DOT:
            dot_next = 1;
            break;
        }
    }; 

    return is_nil(stack) ? NIL : cons_car(cons_list_last(stack));
}
