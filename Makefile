OBJ = getch.o dcl.o

dcl: $(OBJ)
	cc -o dcl $(OBJ)

dcl.o: getch.h

getch.o: 

.PHONY: clean
clean:
	rm -rf dcl *.o
