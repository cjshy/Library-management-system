BOOK:main.o book.o 
	gcc main.o book.o -o BOOK
main.o:main.c 
	gcc -c main.c -o main.o

book.o:book.c 
	gcc -c book.c -o book.o
clear: