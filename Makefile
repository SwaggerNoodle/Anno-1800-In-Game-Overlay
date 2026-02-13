PROGRAM=Anno_1800_In_Game_Overlay.exe
OBJECTS=main.o

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	gcc -Wall -o $(PROGRAM) $(OBJECTS)

main.o: main.c
	gcc -Wall -c main.c

clean:
	rm -f $(OBJECTS) $(PROGRAM)
