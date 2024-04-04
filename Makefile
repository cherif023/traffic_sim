CXX ?= g++

game: main.cpp Car.cpp Car.hpp
	$(CXX) main.cpp Car.cpp -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio