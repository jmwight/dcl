OBJ = getch.o gettoken.o contains.o
ARG = -g3

.PHONY: all
all:
	make dcl undcl

undcl: $(OBJ) undcl.o
	cc $(ARG) -o undcl $(OBJ) undcl.o

dcl: $(OBJ) dcl.o
	cc $(ARG) -o dcl $(OBJ) dcl.o

undcl.o: gettoken.h undcl.c
	cc $(ARG) -c undcl.c

dcl.o: gettoken.h dcl.c contains.h
	cc $(ARG) -c dcl.c

gettoken.o: gettoken.c gettoken.h getch.h
	cc $(ARG) -c gettoken.c

getch.o: getch.c
	cc $(ARG) -c getch.c

contains.o: contains.c
	cc $(ARG) -c contains.c

.PHONY: clean
clean:
	rm -rf dcl undcl *.o
