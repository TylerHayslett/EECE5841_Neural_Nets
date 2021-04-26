all: test_nets 
	
test_nets: test_nets.o matrix_functions.o neural_net.o
	gcc -g -Wall -o test_nets test_nets.o matrix_functions.o neural_net.o -lm -g
	
matrix_functions.o: matrix_functions.c matrix_functions.h common.h
	gcc -g -Wall -c matrix_functions.c
	
neural_net.o: neural_net.c neural_net.h matrix_functions.h common.h
	gcc -g -Wall -c neural_net.c	
	
test_nets.o: test_nets.c matrix_functions.h neural_net.h common.h
	gcc -g -Wall -c test_nets.c 

clean:
	rm *.o
