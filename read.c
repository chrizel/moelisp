#include <ctype.h>
#include <stdio.h>

#include "cons.h"
#include "gc.h"
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
#define TK_QUOTE         6

static inline int is_symbol_char(int c)
{
    return (!isspace(c))
        && (c != '(')
        && (c != ')')
        && (c != ';');
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
    else if (c == '\'')
        return TK_QUOTE;
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

static pobject next_object(char *code, int *start, int *end, int *state)
{
    static const int STATE_EOL   = 1 << 1;
    static const int STATE_DOT   = 1 << 2;
    static const int STATE_QUOTE = 1 << 3;

    pobject result = NIL;

    switch (next_token(code, start, end)) {
    case TK_SYMBOL:
        result = symbol_intern_by_slice(code, *start, *end);
        break;
    case TK_NUMBER:
        result = gc_add( number_new_by_slice(code, *start, *end) );
        break;
    case TK_DOT:
        *state |= STATE_DOT;
        result = next_object(code, start, end, state);
        break;
    case TK_QUOTE:
        *state |= STATE_QUOTE;
        result = next_object(code, start, end, state);
        break;
    case TK_PAREN_OPEN:
        for (;;) {
            int entry_state = 0;
            pobject entry = next_object(code, start, end, &entry_state);
            if (entry_state & STATE_EOL) {
                break;
            } else if (entry_state & STATE_DOT) {
                cons_list_last_cdr_set(&result, entry);
                break;
            } else {
                cons_list_append(&result, entry, 1);
            }
        }
        break;
    case TK_PAREN_CLOSE:
    case TK_EOF:
        *state |= STATE_EOL;
        break;
    }

    if (*state & STATE_QUOTE) {
        result = gc_add( cons_new( symbol_quote,
                    gc_add( cons_new( result, NIL ))));
        *state = *state & ~STATE_QUOTE;
    }

    return result;
}

pobject moe_read(char *code)
{
    int start = 0, end = 0, state = 0;
    return next_object(code, &start, &end, &state);
}
