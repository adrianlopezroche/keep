all: keep

keep: main.o
	gcc main.o -o keep

main.o: main.c
	gcc -c main.c

clean:
	rm -f *.o
	rm -f keep
