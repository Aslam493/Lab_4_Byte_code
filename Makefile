CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main

clean:
	rm -f main
