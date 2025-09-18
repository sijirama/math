CXX = g++
CXXFLAGS = -std=c++23 -O2 -Wall

SRC = $(wildcard *.cpp)

BIN = build/image-kernel

all: $(BIN)

$(BIN): $(SRC)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ $^

run: $(BIN)
	@./$(BIN)

clean:
	rm -rf build
