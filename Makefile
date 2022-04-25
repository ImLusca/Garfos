objects = main.cpp garfos.cpp
all: $(objects)
	g++ $(objects) -o main
run:
	./main