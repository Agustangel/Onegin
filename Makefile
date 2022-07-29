
onegin: main.o onegin.o
	gcc -o onegin main.o onegin.o

main.o: main.c onegin.h
	gcc -c main.c

onegin.o: onegin.c onegin.h
	gcc -c onegin.c

clean:
	rm onegin main.o onegin.o
