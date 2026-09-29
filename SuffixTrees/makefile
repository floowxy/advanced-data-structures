CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -IINCLUDE

TARGET = suffix_trees

SOURCES = APPS/main.cpp \
          SRC/Aplicacion.cpp \
          SRC/SuffixTree.cpp \
          SRC/Ukkonen.cpp \
          SRC/SuffixArray.cpp

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)