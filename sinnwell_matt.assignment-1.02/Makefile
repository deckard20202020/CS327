# all: main.c terrain.c terrain.h 
# 	gcc -g main.c terrain.c terrain.h -o main -Wall -Werror

# clean:
# 	rm -f *.o main.o

all: main 

main: terrain.o main.o 
	gcc terrain.o main.o -o main

main.o: main.c
	gcc -Wall -Werror -g main.c -c -g

terrain.o: terrain.c
	gcc -Wall -Werror -g terrain.c -c -g

clean:
	rm -f *.o main
