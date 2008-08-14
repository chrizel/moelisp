#include <ctype.h>
#include <stdio.h>

#include "cons.h"
#include "object.h"
#include "read.h"
#include "symbol.h"

#define TK_EOF           0
#define TK_PAREN_OPEN    1
#define TK_PAREN_CLOSE   2
#define TK_SYMBOL        3
#define TK_NUMBER        4

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
        || (c == '?');
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

    while (code[*start] && (skip_spaces(code, start) || skip_comments(code, start)))
        ;

    *end = *start + 1;
    c = code[*start];
    if (c == '(')
        return TK_PAREN_OPEN;
    else if (c == ')')
        return TK_PAREN_CLOSE;
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

static int internal_read(char *code, pobject *dest, int *start, int *end)
{
    pobject tmp;
    int type;
    type = next_token(code, &start, &end);
    switch (type) {
    case TK_SYMBOL:
        *dest = symbol_create_by_slice(code, *start, *end);
        break;
    case TK_PAREN_OPEN:
        *dest = cons_new(NIL, NIL);
        *start = *end;
        while (type = internal_read(code, &cons_car(*dest), start, end)) {
            if (type == TK_PAREN_CLOSE)
                break;
            *start = *end;

        }
        break;
    }

    *start = *end;
    return type;

    /*
    while (type = next_token(code, &start, &end)) {
        if (type == TK_SYMBOL) {
            o = symbol_new_by_slice(code, start, end);
            printf("symbol: \"%s\"\n", symbol_value(o));
            object_free(o);
        } else {
            printf("%d: %d-%d\n", type, start, end - 1);
        }
        start = end;
    }
    */
}

pobject read(char *code)
{
    pobject result;
    int start = 0, int end = 0;
    internal_read(code, &result, &start, &end);
    return result;
}
