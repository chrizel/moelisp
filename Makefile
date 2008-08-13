BINARY  = moe
SOURCES = object.c number.c character.c cons.c parser.c moe.c
HEADERS = object.h number.h character.h cons.h

$(BINARY): $(SOURCES) $(HEADERS)
	gcc -g -o $(BINARY) $(SOURCES)

clean:
	rm -rf $(BINARY) *.o
