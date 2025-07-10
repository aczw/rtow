CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2
SRC_DIR := src
BUILD_DIR := build

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
TARGET := rtow

default: all run open

all: $(TARGET)

# For each source file ($<), compile it to an object file ($@)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link all objects ($^) together into the target ($@)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

run:
	./rtow > image.ppm

clean:
	rm -rf $(BUILD_DIR) $(TARGET) image.ppm

open:
	open image.ppm

.PHONY: default all run clean open
