CC = g++
VERSION = -std=c++17
DEEPINS = -ljsoncpp
all : main.cpp
	$(CC) $(VERSION) $(DEEPINS) main.cpp -o main
run : main 
	./main
