PROG = compiler
FLAGS = -g -Wall -fsanitize=address -fno-omit-frame-pointer
CC = g++

$(PROG): main.cpp lex.o
	$(CC) $(FLAGS) -c lex.cpp -o lex.o
	$(CC) $(FLAGS) main.cpp lex.o -o $(PROG)
clean:
	rm -f *.o $(PROG)