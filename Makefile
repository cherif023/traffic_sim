CXX ?= g++

game: main.cpp Car.cpp
	$(CXX) main.cpp Car.cpp -o $@ -lsfml-graphics -lsfml-window -lsfml-system