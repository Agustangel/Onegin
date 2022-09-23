
INCLUDES=include
SOURCE=source
SORTING=sorting

#добавить санитайзеры leak address

onegin: main.o onegin.o insertion_sort.o
	gcc -o onegin main.o onegin.o insertion_sort.o

main.o: main.c ${INCLUDES}/onegin.h
	gcc -g -O0 -I ${INCLUDES} -c main.c

onegin.o: ${SOURCE}/onegin.c ${INCLUDES}/onegin.h
	gcc -g -O0 -I ${INCLUDES} -c ${SOURCE}/onegin.c

insertion_sort.o: ${SORTING}/insertion_sort.c ${INCLUDES}/onegin.h
	gcc -g -O0 -I ${INCLUDES} -c ${SORTING}/insertion_sort.c


sanitize: main.o onegin.o insertion_sort.o
	gcc -o onegin main.o onegin.o insertion_sort.o -fsanitize=address -g


valgrind: onegin
	valgrind --leak-check=yes ./onegin $(ARGS)

clean:
	rm onegin main.o onegin.o insertion_sort.o
