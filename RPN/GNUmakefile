all: Lab4

Lab4: Lab04_main.c rpn.o stack.o
	gcc -Wall Lab04_main.c rpn.o stack.o BOARD.c -o Lab4

stack_test: stack_test.c stack.o 
	gcc -Wall stack_test.c stack.o BOARD.c -o stack_test

rpn_test: rpn_test.c rpn.o stack.o
	gcc -Wall rpn_test.c rpn.o stack.o BOARD.c -o rpn_test

stack.o: stack.c
	gcc -Wall -c stack.c

rpn.o: rpn.c
	gcc -Wall -c rpn.c

