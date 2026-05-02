CXX = g++
CC = gcc
CFLAGS = -c -Wall
CXXFLAGS = -c -Wall -std=c++11
LDFLAGS = -lstdc++

TARGET = app
SOURCES_C = src/inventory.c
SOURCES_CPP = src/main.cpp src/InventoryManager.cpp
OBJECTS = $(SOURCES_C:.c=.o) $(SOURCES_CPP:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

src/inventory.o: src/inventory.c include/inventory.h
	$(CC) $(CFLAGS) src/inventory.c -o src/inventory.o

src/main.o: src/main.cpp src/InventoryManager.h
	$(CXX) $(CXXFLAGS) src/main.cpp -o src/main.o

src/InventoryManager.o: src/InventoryManager.cpp src/InventoryManager.h include/inventory.h
	$(CXX) $(CXXFLAGS) src/InventoryManager.cpp -o src/InventoryManager.o

clean:
	rm -f src/*.o $(TARGET)

.PHONY: all clean
