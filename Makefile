CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2
INCLUDES := -Iinclude

BUILD_DIR := build
SRC_DIR   := src
TEST_DIR  := tests

ifeq ($(OS),Windows_NT)
EXE := .exe
else
EXE :=
endif

TARGET      := $(BUILD_DIR)/organizer$(EXE)
TEST_TARGET := $(BUILD_DIR)/tests$(EXE)

SRCS      := $(wildcard $(SRC_DIR)/*.cpp)
LIB_SRCS  := $(filter-out $(SRC_DIR)/main.cpp,$(SRCS))
OBJS      := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
LIB_OBJS  := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(LIB_SRCS))
TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS := $(BUILD_DIR)/CLI.o $(BUILD_DIR)/FileInfo.o $(BUILD_DIR)/Rule.o

.PHONY: all test run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Tests only need the modules that don't depend on nlohmann/json.
$(TEST_TARGET): $(TEST_SRCS) $(TEST_OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(TEST_SRCS) $(TEST_OBJS) -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

run: $(TARGET)
	./$(TARGET) --help

clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d $(TARGET) $(TEST_TARGET)

-include $(OBJS:.o=.d)
