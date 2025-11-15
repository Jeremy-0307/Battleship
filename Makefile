CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude -g
LIBS = -lncurses
SRC = src
BIN = bin
BUILD = build

SRCS := $(wildcard $(SRC)/*.cpp)
OBJS := $(patsubst $(SRC)/%.cpp, $(BUILD)/%.o, $(SRCS))
TARGET = $(BIN)/battleship

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN)
	$(CXX) $(OBJS) -o $@ $(LIBS)

$(BUILD)/%.o: $(SRC)/%.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN) $(BUILD):
	mkdir -p $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD) $(BIN)

.PHONY: all clean run
