PROGRAM=Anno_1800_In_Game_Overlay.exe
OBJECTS=main_noDebug.o
LDLIBS=-lcomctl32 -luser32 -lgdi32

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	gcc -Wall -o $(PROGRAM) $(OBJECTS) $(LDLIBS)

main_noDebug.o: main_noDebug.c
	gcc -Wall -c main_noDebug.c

clean:
	rm -f $(OBJECTS) $(PROGRAM)
