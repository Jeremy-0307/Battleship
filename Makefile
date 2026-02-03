CXX = g++
SRC = src
BIN = bin
BUILD = build
TARGET = $(BIN)/battleship

# --- Warnings ---
WARNINGS = -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion \
           -Wnull-dereference -Wdouble-promotion -Wformat=2

# --- Sanitizers (runtime checks) ---
SANITIZERS = -fsanitize=address,undefined -fno-omit-frame-pointer

CXXFLAGS = -std=c++20 -Iinclude -g $(WARNINGS) $(SANITIZERS)
LDFLAGS  = $(SANITIZERS)
LIBS = -lncurses

SRCS := $(wildcard $(SRC)/*.cpp)
OBJS := $(patsubst $(SRC)/%.cpp,$(BUILD)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LIBS)

$(BUILD)/%.o: $(SRC)/%.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN) $(BUILD):
	mkdir -p $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD) $(BIN)

.PHONY: all clean run
