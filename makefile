PROG = compiler
FLAGS = -g -Wall -fsanitize=address -fno-omit-frame-pointer
CC = g++

$(PROG): main.cpp lex.o poliz.o syntax.o Table.o execute.o
	$(CC) $(FLAGS) -c lex.cpp -o lex.o
	$(CC) $(FLAGS) -c poliz.cpp -o poliz.o
	$(CC) $(FLAGS) -c syntax.cpp -o syntax.o
	$(CC) $(FLAGS) -c Table.c -o Table.o
	$(CC) $(FLAGS) -c execute.cpp -o execute.o
	$(CC) $(FLAGS) main.cpp lex.o poliz.o syntax.o Table.o execute.o -o $(PROG)
clean:
	rm -f *.o $(PROG)