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

# all: main 

# main: characterQ.o pq.o heap.o terrain.o main.o 
# 	gcc characterQ.o pq.o heap.o terrain.o main.o -lncurses -o main

# main.o: main.c
# 	gcc -Wall -Werror -g main.c -c -g

# terrain.o: terrain.c
# 	gcc -Wall -Werror -g terrain.c -c -g

# heap.o: heap.c
# 	gcc -Wall -Werror -g heap.c -c -g

# pq.o: pq.c
# 	gcc -Wall -Werror -g pq.c -c -g

# characterQ.o: characterQ.c
# 	gcc -Wall -Werror -g characterQ.c -c -g

# clean:
# 	rm -f *.o main

all: main

-include main.d terrain.d pq.d characterQ.d db_parse.d

main: characterQ.o pq.o terrain.o db_parse.o main.o 
	g++ -o main characterQ.o pq.o terrain.o  db_parse.o main.o -lncurses

main.o:
	g++ -c -I -Wall -Werror -g main.cpp -MMD -MF main.d -g

terrain.o:
	g++ -c -I -Wall -Werror -g terrain.cpp -MMD -MF terrain.d -g

pq.o:
	g++ -c -I -Wall -Werror -g pq.cpp -MMD -MF pq.d -g

characterQ.o:
	g++ -c -I -Wall -Werror -g characterQ.cpp -MMD -MF characterQ.d -g

db_parse.o:
	g++ -c -I -Wall -Werror -g db_parse.cpp -MMD -MF db_parse.d -g

clean:
	rm -f *.o *.d main
