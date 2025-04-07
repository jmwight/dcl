OBJ = getch.o dcl.o gettoken.o

dcl: $(OBJ)
	cc -o dcl $(OBJ)

dcl.o: getch.h

gettoken.o: gettoken.h getch.h

getch.o: 

.PHONY: clean
clean:
	rm -rf dcl *.o
