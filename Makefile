CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2

all: clean build run

build: src/main.cpp
	$(CXX) $(CXXFLAGS) -o rtow src/main.cpp

run:
	./rtow > image.ppm

clean:
	rm -rf image.ppm rtow

.PHONY: all run clean
