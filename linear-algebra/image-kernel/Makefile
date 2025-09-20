
CXX = g++

OPENCV_CFLAGS = $(shell pkg-config --cflags opencv4)
OPENCV_LIBS   = $(shell pkg-config --libs opencv4)

CXXFLAGS = -std=c++23 -O2 $(OPENCV_CFLAGS)
LDFLAGS  = $(OPENCV_LIBS)

SRC = $(wildcard *.cpp)
BIN = build/image-kernel

all: $(BIN)

$(BIN): $(SRC)
	@mkdir -p build
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

run: $(BIN)
	@./$(BIN)

clean:
	rm -rf build
