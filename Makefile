# Data Structures in C — GNU Make build
#
# Version 0.2.0
#
# Common commands:
#   make                          Build the library and demo (debug)
#   make test                     Build and run the unit tests
#   make BUILD=release            Build optimized artifacts
#   make BUILD=sanitize test      Build and run tests with sanitizers
#   make clean                    Remove the selected configuration
#   make clean-all                Remove every configuration

.DEFAULT_GOAL := all
.SUFFIXES:

# TODO: add -DNDEBUG after all test

# -- Project layout -----------------------------------------------------------
# Project configuration
PROJECT := ds

# Source directories
SRC_DIR := src

# Include directories
INCLUDE_DIR := include
PUBLIC_DIR  := $(INCLUDE_DIR)/ds

# Test directories
TEST_DIR := tests

# Example directories
EXAMPLE_DIR         := examples
EXAMPLE_SRC_DIR     := $(EXAMPLE_DIR)/src
EXAMPLE_INCLUDE_DIR := $(EXAMPLE_DIR)/include

# Keep debug, release and sanitizer objects separate so switching BUILD
# never reuses objects compiled with incompatible flags.

# Build configuration
BUILD      ?= debug
BUILD_ROOT ?= build
BUILD_DIR  ?= $(BUILD_ROOT)/$(BUILD)

# Object directories
OBJ_DIR      := $(BUILD_DIR)/obj

LIB_OBJ_DIR  := $(OBJ_DIR)/$(SRC_DIR)
TEST_OBJ_DIR := $(OBJ_DIR)/$(TEST_DIR)
DEMO_OBJ_DIR := $(OBJ_DIR)/$(EXAMPLE_SRC_DIR)

# Output directories
BIN_DIR := $(BUILD_DIR)/bin
LIB_DIR := $(BUILD_DIR)/lib

# Build artifacts
LIBRARY     := $(LIB_DIR)/lib$(PROJECT).a
DEMO        := $(BIN_DIR)/$(PROJECT)-demo
TEST_RUNNER := $(BIN_DIR)/$(PROJECT)-tests

# -- Installation -------------------------------------------------------------
# PREFIX is the logical install prefix. DESTDIR is an optional staging root
# used by packagers; it is prepended to install paths without changing PREFIX.

# Installation directories
PREFIX     ?= /usr/local
LIBDIR     ?= $(PREFIX)/lib
#Ex: make install DESTDIR="/tmp/package"
DESTDIR    ?=
INCLUDEDIR ?= $(PREFIX)/include
DOCDIR     ?= $(PREFIX)/share/doc/$(PROJECT)

# Installation command
INSTALL ?= install

# Public headers
PUBLIC_HEADERS      := $(sort $(wildcard $(PUBLIC_DIR)/*.h)) # Find, sort and remove duplicates
PUBLIC_HEADER_NAMES := $(notdir $(PUBLIC_HEADERS))          # Extract filenames without directory paths

# -- Toolchain ----------------------------------------------------------------
# ex: ar rcs libds.a stack.o queue.o linked_list.o

# Toolchain configuration
CC ?= cc # generic compiler
AR ?= ar # archive (use to create static librairy .a)

# Archive flags
ARFLAGS := rcs

# Preprocessor flags
CPPFLAGS += -I$(INCLUDE_DIR) -I$(EXAMPLE_INCLUDE_DIR)

# Compiler standard
CFLAGS ?= -std=c11

# Warning flags
WARNINGS := -Wall -Wextra -Wpedantic -Werror

# Dependency generation flags
DEPFLAGS = -MMD -MP

# Build modes
ifeq ($(BUILD),debug)
  # Disable optimizations and enable detailed debugging information
  BUILD_CFLAGS := -O0 -g3

else ifeq ($(BUILD),release)
  # Enable optimizations while keeping assertions enabled
  # The test suite relies on assert() (add -DNDEBUG after all test)
  BUILD_CFLAGS := -O2

else ifeq ($(BUILD),sanitize)
  # Enable moderate optimizations, debugging information and runtime sanitizers.
  # Preserve stack frames for more accurate error reports.
  BUILD_CFLAGS  := -O1 -g3 -fno-omit-frame-pointer -fsanitize=address,undefined
  BUILD_LDFLAGS := -fsanitize=address,undefined

else
  # Reject unsupported build modes.
  $(error Unsupported BUILD '$(BUILD)'; choose debug, release, or sanitize)
endif

# Combined compiler flags
ALL_CFLAGS = $(CFLAGS) $(WARNINGS) $(BUILD_CFLAGS)

# Combined linker flags
# Linker flags
# Ex: make LDFLAGS ="-L/usr/local/lib"
LDFLAGS ?=
ALL_LDFLAGS = $(LDFLAGS) $(BUILD_LDFLAGS)

# -- Sources and artifacts ----------------------------------------------------
# Sources
LIB_SOURCES  := $(sort $(wildcard $(SRC_DIR)/*.c))
TEST_SOURCES := $(sort $(wildcard $(TEST_DIR)/*.c))
DEMO_SOURCES := $(sort $(wildcard $(EXAMPLE_SRC_DIR)/*.c))

# Object files
LIB_OBJECTS  := $(patsubst $(SRC_DIR)/%.c,$(LIB_OBJ_DIR)/%.o,$(LIB_SOURCES))
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.c,$(TEST_OBJ_DIR)/%.o,$(TEST_SOURCES))
DEMO_OBJECTS := $(patsubst $(EXAMPLE_SRC_DIR)/%.c,$(DEMO_OBJ_DIR)/%.o,$(DEMO_SOURCES))

# Dependency files
DEPFILES := $(LIB_OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d) $(DEMO_OBJECTS:.o=.d)

# -- User-facing targets ------------------------------------------------------
# Phony targets
.PHONY: all build library demo run test check install uninstall clean clean-all help

# Main targets
all: library demo
build: all

# Build targets
library: $(LIBRARY)
demo: $(DEMO)

# Test targets
test: $(TEST_RUNNER)
	@echo "Running $(TEST_RUNNER)"
	@$(TEST_RUNNER)

check: test

# Execution targets
run: $(DEMO)
	@$(DEMO)

# Installation targets
# Ex: /usr/local/lib/libds.a
install: $(LIBRARY)
	$(INSTALL) -d "$(DESTDIR)$(LIBDIR)" "$(DESTDIR)$(INCLUDEDIR)/$(PROJECT)" "$(DESTDIR)$(DOCDIR)"
	$(INSTALL) -m 644 $(LIBRARY) "$(DESTDIR)$(LIBDIR)/lib$(PROJECT).a"
	$(INSTALL) -m 644 $(PUBLIC_HEADERS) "$(DESTDIR)$(INCLUDEDIR)/$(PROJECT)/"
	$(INSTALL) -m 644 README.md LICENSE "$(DESTDIR)$(DOCDIR)/"

# Uninstallation targets
# check dependance with install before uninstall
uninstall:
	$(RM) "$(DESTDIR)$(LIBDIR)/lib$(PROJECT).a"
	@for header in $(PUBLIC_HEADER_NAMES); do \
	  $(RM) "$(DESTDIR)$(INCLUDEDIR)/$(PROJECT)/$$header"; \
	done
	$(RM) "$(DESTDIR)$(DOCDIR)/README.md" "$(DESTDIR)$(DOCDIR)/LICENSE"
	@rmdir "$(DESTDIR)$(INCLUDEDIR)/$(PROJECT)" "$(DESTDIR)$(DOCDIR)" 2>/dev/null || true

# -- Link/archive -------------------------------------------------------------
# Build the static library
# Ex: ar rcs build/debug/lib/libds.a build/debug/obj/src/stack.o build/debug/obj/src/queue.o
$(LIBRARY): $(LIB_OBJECTS) | $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^

# Build the demo executable
# Ex: cc -std=c11 -Wall -Wextra -Wpedantic -Werror \
# build/debug/obj/examples/src/main.o \
# build/debug/lib/libds.a \
# -o build/debug/bin/demo
$(DEMO): $(DEMO_OBJECTS) $(LIBRARY) | $(BIN_DIR)
	$(CC) $(ALL_CFLAGS) $(ALL_LDFLAGS) $(DEMO_OBJECTS) $(LIBRARY) $(LDLIBS) -o $@

# Build the test executable
$(TEST_RUNNER): $(TEST_OBJECTS) $(LIBRARY) | $(BIN_DIR)
	$(CC) $(ALL_CFLAGS) $(ALL_LDFLAGS) $(TEST_OBJECTS) $(LIBRARY) $(LDLIBS) -o $@

# -- Compilation --------------------------------------------------------------
# Compile library sources
$(LIB_OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(LIB_OBJ_DIR)
	$(CC) $(CPPFLAGS) $(ALL_CFLAGS) $(DEPFLAGS) -c $< -o $@

# Compile test sources
$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(TEST_OBJ_DIR)
	$(CC) $(CPPFLAGS) $(ALL_CFLAGS) $(DEPFLAGS) -c $< -o $@

# Compile demo sources
$(DEMO_OBJ_DIR)/%.o: $(EXAMPLE_SRC_DIR)/%.c | $(DEMO_OBJ_DIR)
	$(CC) $(CPPFLAGS) $(ALL_CFLAGS) $(DEPFLAGS) -c $< -o $@

# Order-only prerequisites keep directory timestamps from forcing rebuilds.
$(LIB_OBJ_DIR) $(TEST_OBJ_DIR) $(DEMO_OBJ_DIR) $(BIN_DIR) $(LIB_DIR):
	@mkdir -p $@

# -- Maintenance --------------------------------------------------------------
clean:
	$(RM) -r $(BUILD_DIR)

clean-all:
	$(RM) -r $(BUILD_ROOT)

help:
	@printf '%s\n' \
	  'Data Structures in C — build help' \
	  '' \
	  'Targets:' \
	  '  all (default)   Build the static library and interactive demo.' \
	  '  build           Alias for all.' \
	  '  library         Build build/<BUILD>/lib/libds.a.' \
	  '  demo            Build build/<BUILD>/bin/ds-demo.' \
	  '  run             Build and launch the interactive demo.' \
	  '  test            Build and run the unit test suite.' \
	  '  check           Alias for test.' \
	  '  install         Build and install the library, public headers, and docs.' \
	  '  uninstall       Remove only the files installed by this project.' \
	  '  clean           Remove artifacts for the selected BUILD mode.' \
	  '  clean-all       Remove the complete build/ directory.' \
	  '  help            Display this help.' \
	  '' \
	  'Build modes (select with BUILD=<mode>; default: debug):' \
	  '  debug           No optimization; includes debug symbols.' \
	  '  release         Optimized build; assertions remain enabled.' \
	  '  sanitize        AddressSanitizer and UndefinedBehaviorSanitizer.' \
	  '' \
	  'Configurable variables:' \
	  '  CC              C compiler (default: make built-in, usually cc).' \
	  '  AR              Static library archiver.' \
	  '  ARFLAGS         Archiver options (Makefile default: rcs).' \
	  '  BUILD           Build mode: debug, release, or sanitize.' \
	  '  BUILD_ROOT      Root for generated files (default: build).' \
	  '  BUILD_DIR       Selected mode directory (default: BUILD_ROOT/BUILD).' \
	  '  PREFIX          Installation prefix (default: /usr/local).' \
	  '  LIBDIR          Library install directory (default: PREFIX/lib).' \
	  '  INCLUDEDIR      Header install directory (default: PREFIX/include).' \
	  '  DOCDIR          Documentation directory (default: PREFIX/share/doc/ds).' \
	  '  DESTDIR         Optional staging root for install/uninstall.' \
	  '  CPPFLAGS        Preprocessor options; include paths are added by Makefile.' \
	  '  CFLAGS          C compiler options.' \
	  '  LDFLAGS         Linker options.' \
	  '  LDLIBS          Libraries passed to the linker.' \
	  '' \
	  'Examples:' \
	  '  make' \
	  '  make run' \
	  '  make test BUILD=release' \
	  '  make BUILD=sanitize test' \
	  '  make CC=clang all' \
	  '  sudo make install' \
	  '  sudo make uninstall' \
	  '  make install PREFIX=/opt/ds DESTDIR=/tmp/package' \
	  '  make clean BUILD=debug' \
	  '  make clean-all'

-include $(DEPFILES)
