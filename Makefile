all: tests main

tests: tests.cpp
	g++ tests.cpp -lGL -lGLU -lglut -o tests

main: main.cpp
	g++ main.cpp -lGL -lGLU -lglut -o main

clean:
	rm tests main
