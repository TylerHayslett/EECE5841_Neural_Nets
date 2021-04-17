all: test_nets 
	
test_nets: test_nets.o image_functions.o matrix_functions.o 
	gcc -g -Wall -o test_nets test_nets.o image_functions.o matrix_functions.o -lm

image_functions.o: image_functions.c image_functions.h common_deffs.h
	gcc -g -Wall -c image_functions.c
	
matrix_functions.o: matrix_functions.c matrix_functions.h common_deffs.h
	gcc -g -Wall -c matrix_functions.c
	
test_nets.o: test_nets.c image_functions.h matrix_functions.h common_deffs.h
	gcc -g -Wall -c test_nets.c 

clean:
	rm *.o
