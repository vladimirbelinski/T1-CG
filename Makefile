all: main robot skate

main: main.cpp
	g++ main.cpp -lGL -lGLU -lglut -o main

robot: robot.cpp
	g++ robot.cpp -lGL -lGLU -lglut -o robot

skate: skate.cpp
	g++ skate.cpp -lGL -lGLU -lglut -o skate

clean:
	rm main robot skate
