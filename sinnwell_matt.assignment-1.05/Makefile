# all: main.c terrain.c terrain.h 
# 	gcc -g main.c terrain.c terrain.h -o main -Wall -Werror

# clean:
# 	rm -f *.o main.o

# all: main 

# main: terrain.o main.o 
# 	gcc terrain.o main.o -o main

# main.o: main.c
# 	gcc -Wall -Werror -g main.c -c -g

# terrain.o: terrain.c
# 	gcc -Wall -Werror -g terrain.c -c -g

# clean:
# 	rm -f *.o main

# gcc ncursesdemo.c -std=c99 -lncurses -o ncursesdemo

all: main 

main: characterQ.o pq.o heap.o terrain.o main.o 
	gcc characterQ.o pq.o heap.o terrain.o main.o -lncurses -o main

main.o: main.c
	gcc -Wall -Werror -g main.c -c -g

terrain.o: terrain.c
	gcc -Wall -Werror -g terrain.c -c -g

heap.o: heap.c
	gcc -Wall -Werror -g heap.c -c -g

pq.o: pq.c
	gcc -Wall -Werror -g pq.c -c -g

characterQ.o: characterQ.c
	gcc -Wall -Werror -g characterQ.c -c -g

clean:
	rm -f *.o main
