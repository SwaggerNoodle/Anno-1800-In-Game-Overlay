PROGRAM=Anno_1800_In_Game_Overlay.exe
OBJECTS=main_noDebug.o

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	gcc -Wall -o $(PROGRAM) $(OBJECTS)

main_noDebug.o: main_noDebug.c
	gcc -Wall -c main_noDebug.c

clean:
	rm -f $(OBJECTS) $(PROGRAM)
