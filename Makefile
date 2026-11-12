# PROJECT CONFIGURATION

# Define directories for build artifacts
BUILD_DIR := build
OBJ_DIR   := $(BUILD_DIR)/obj
BIN_DIR   := $(BUILD_DIR)/bin

# Define source directories
SRC_DIR   := src
INC_DIR   := include
TEST_DIR  := tests


# SOURCE FILES

# Main application source file
APP_SRCS  := $(SRC_DIR)/main.c

# Collect all project source files except main.c
# These files form the data structures library
LIB_SRCS  := $(filter-out $(APP_SRCS), $(wildcard $(SRC_DIR)/*.c))

# Collect all test source files
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)


# OBJECT FILES

# Generate object file paths for the application
APP_OBJS  := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(APP_SRCS))

# Generate object file paths for the library
LIB_OBJS  := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(LIB_SRCS))

# Generate object file paths for the tests
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRCS))

# Combine application and library object files
OBJS := $(APP_OBJS) $(LIB_OBJS)


# EXECUTABLES

# Define output executable paths
TARGET    := $(BIN_DIR)/main.exe
TEST_BIN  := $(BIN_DIR)/test.exe


# TOOLCHAIN CONFIGURATION

# Select the C compiler
CC := clang

# Common compiler flags
# -std=c11 : Use the C11 standard
# -Wall    : Enable common warnings
# -Wextra  : Enable additional warnings
# -Werror  : Treat warnings as errors
# -Wpedantic : Enforce strict ISO C compliance
# -I       : Specify the header files directory
# -MMD     : Generate dependency files for user headers
# -MP      : Add dummy rules for header dependencies
CFLAGS_COMMON := -std=c11 -Wall -Wextra -Werror -Wpedantic \
                 -I$(INC_DIR) -MMD -MP

# Debug configuration
# -g  : Generate debugging information
# -O0 : Disable compiler optimizations
CFLAGS_DEBUG   := $(CFLAGS_COMMON) -g -O0

# Release configuration
# -O2 : Enable compiler optimizations
CFLAGS_RELEASE := $(CFLAGS_COMMON) -O2

# Select the build configuration (debug by default)
BUILD ?= debug

ifeq ($(BUILD),release)
	CFLAGS := $(CFLAGS_RELEASE)
else
	CFLAGS := $(CFLAGS_DEBUG)
endif


# MAIN RULES

# Build the application, run tests, then execute the application
all: build test run

# Build the main executable
build: $(TARGET)

# Execute the main application
run: $(TARGET)
	./$(TARGET)

# Build and execute the test suite
test: $(TEST_BIN)
	./$(TEST_BIN)


# LINKING

# Link application and library object files
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Link test and library object files
$(TEST_BIN): $(TEST_OBJS) $(LIB_OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@


# COMPILATION

# Compile application and library source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test source files into object files
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


# DIRECTORY CREATION

# Create the object files directory if it does not exist
$(OBJ_DIR):
	mkdir -p $@

# Create the executable files directory if it does not exist
$(BIN_DIR):
	mkdir -p $@


# CLEANUP

# Remove all generated build files
clean:
	rm -rf $(BUILD_DIR)

# Clean the project and rebuild everything
re: clean all


# AUTOMATIC DEPENDENCIES

# Collect generated dependency files
DEPS := $(APP_OBJS:.o=.d) $(LIB_OBJS:.o=.d) $(TEST_OBJS:.o=.d)

# Include dependency files if they exist
-include $(DEPS)


# PHONY TARGETS

# Declare targets that do not represent actual files
.PHONY: all build run test clean re
