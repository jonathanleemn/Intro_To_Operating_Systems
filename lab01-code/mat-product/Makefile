CFLAGS = -Wall -g
CC     = gcc $(CFLAGS)


all : op_main

outer_product.o : outer_product.c mat.h
	$(CC) -c outer_product.c

free_matrix.o : free_matrix.c mat.h
	$(CC) -c free_matrix.c

op_main.o : op_main.c mat.h
	$(CC) -c op_main.c

op_main : op_main.o outer_product.o free_matrix.o
	$(CC) -o op_main op_main.o outer_product.o free_matrix.o

test_outer_product.o : test_outer_product.c mat.h
	$(CC) -c test_outer_product.c

test_outer_product : test_outer_product.o outer_product.o
	$(CC) -o test_outer_product.o outer_product.o

test : test_outer_product
	./test_outer_product

clean:
	rm -f *.o op_main test_outer_product
