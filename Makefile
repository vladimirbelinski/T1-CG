all:
	g++ *.cpp -lGL -lGLU -lglut -o main

clean:
	rm main
