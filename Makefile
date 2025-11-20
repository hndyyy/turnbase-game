CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Isrc/cpp -Isrc/header

SRCS := $(wildcard src/cpp/*.cpp)
TARGET := game.exe

.PHONY: all clean

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o
