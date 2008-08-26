BINARY  = moe
SOURCES = object.c number.c character.c cons.c symbol.c read.c print.c eval.c cfunc.c builtin_core.c builtin_math.c env.c closure.c macro.c gc.c moe.c
HEADERS = object.h number.h character.h cons.h symbol.h read.h print.h eval.h cfunc.h builtin_core.h builtin_math.h env.h closure.h macro.h gc.h

$(BINARY): $(SOURCES) $(HEADERS)
	gcc -Wall -lm -g -o $(BINARY) $(SOURCES)

clean:
	rm -rf $(BINARY) *.o
