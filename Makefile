PROGRAM=Anno_1800_In_Game_Overlay.exe
OBJECTS=main.o helpers.o
LDLIBS=-lcomctl32 -luser32 -lgdi32

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	gcc -Wall -o $(PROGRAM) $(OBJECTS) $(LDLIBS)



main.o: main.c helpers.h dataStructs.h
	gcc -Wall -c main.c

helpers.o: helpers.c helpers.h dataStructs.h
	gcc -Wall -c helpers.c



clean:
	rm -f $(OBJECTS) $(PROGRAM)
