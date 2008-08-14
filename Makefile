BINARY  = moe
SOURCES = object.c number.c character.c cons.c symbol.c read.c print.c moe.c
HEADERS = object.h number.h character.h cons.h symbol.h read.h print.h

$(BINARY): $(SOURCES) $(HEADERS)
	gcc -g -o $(BINARY) $(SOURCES)

clean:
	rm -rf $(BINARY) *.o
