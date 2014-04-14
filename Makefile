all: exec

run: exec
	./exec
exec: main.o
	g++ main.o -l glut  -o exec
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm -rf *.o
