all: tests main skate

tests: tests.cpp
	g++ tests.cpp -lGL -lGLU -lglut -o tests

main: main.cpp
	g++ main.cpp -lGL -lGLU -lglut -o main

skate: skate.cpp
	g++ skate.cpp -lGL -lGLU -lglut -o skate

clean:
	rm tests main skate
