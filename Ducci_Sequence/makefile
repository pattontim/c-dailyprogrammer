ducci: main.cpp ducci.cpp ducci.h utility.cpp utility.h
	g++ -c -std=c++11 utility.cpp ducci.cpp main.cpp -I.
	g++ utility.o ducci.o main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm ducci.o main.o utility.o sfml-app
