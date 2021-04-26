hw3: main.o parser.o compiler.o
	gcc -o hw4 main.o parser.o compiler.o

main.o: main.c parser.h
	gcc -c main.c

parser.o: parser.c parser.h
	gcc -c parser.c

compiler.o: compiler.c parser.h compiler.h
	gcc -c compiler.c

clean:
	rm *.o
	rm hw4
