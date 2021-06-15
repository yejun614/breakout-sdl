CC=g++
CXXFLAGS=-lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer --std=c++11 -Wall -objC -g
TARGET=./bin/game.out
OBJS=entity/block.o entity/paddle.o entity/ball.o utility/text.o utility/shapes.o game.o main.o

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $(OBJS)

block.o : entity/block.cpp
	$(CC) $(CXXFLAGS) -c -o block.o entity/block.cpp

paddle.o : entity/paddle.cpp
	$(CC) $(CXXFLAGS) -c -o paddle.o entity/paddle.cpp

ball.o : entity/ball.cpp
	$(CC) $(CXXFLAGS) -c -o ball.o entity/ball.cpp

text.o : utility/text.cpp
	$(CC) $(CXXFLAGS) -c -o text.o utility/text.cpp

shape.o : utility/shapes.cpp
	$(CC) $(CXXFLAGS) -c -o shapes.o utility/shapes.cpp

game.o : game.cpp
	$(CC) $(CXXFLAGS) -c -o game.o game.cpp

main.o : main.cpp
	$(CC) $(CXXFLAGS) -c -o main.o main.cpp

clean:
	rm $(OBJS) $(TARGET)
