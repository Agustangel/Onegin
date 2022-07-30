
INCLUDES=include
SOURCE=source

onegin: main.o onegin.o
	gcc -o onegin main.o onegin.o

main.o: main.c ${INCLUDES}/onegin.h
	gcc -g -O0 -I ${INCLUDES} -c main.c

onegin.o: ${SOURCE}/onegin.c ${INCLUDES}/onegin.h
	gcc -g -O0 -I ${INCLUDES} -c ${SOURCE}/onegin.c

clean:
	rm onegin main.o onegin.o
