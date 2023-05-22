# Makefile to compile main.cpp and tests to WebAssembly

# Compiler
CC := emcc
# Compiler flags
CFLAGS := -std=c++11 -Wall -g
# Linker flags
LDFLAGS := -s WASM=1

# Directories
SRCDIR := src
COREDIR := $(SRCDIR)/core
EMUDIR := $(SRCDIR)/emu
TESTDIR := test
OBJDIR := output
APPDIR := app/build

# Source files
CORE_SRCS := $(wildcard $(COREDIR)/*.cpp)
EMU_SRCS := $(wildcard $(EMUDIR)/*.cpp)
TEST_SRCS := $(wildcard $(TESTDIR)/cpu/*.cpp)

# Object files
CORE_OBJS := $(patsubst $(COREDIR)/%.cpp,$(OBJDIR)/core/%.o,$(CORE_SRCS))
EMU_OBJS := $(patsubst $(EMUDIR)/%.cpp,$(OBJDIR)/emu/%.o,$(EMU_SRCS))
TEST_OBJS := $(patsubst $(TESTDIR)/cpu/%.cpp,$(OBJDIR)/test/%.o,$(TEST_SRCS))

# Executable name
EXECUTABLE := $(APPDIR)/index.html
TEST_EXECUTABLE := $(APPDIR)/test.html

# Default target
all: $(EXECUTABLE)

# Link the object files for main.cpp to create the executable
$(EXECUTABLE): $(CORE_OBJS) $(EMU_OBJS) $(OBJDIR)/emu/main.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# Compile the source files for core
$(OBJDIR)/core/%.o: $(COREDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Compile the source files for emu
$(OBJDIR)/emu/%.o: $(EMUDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_EXECUTABLE)

# Link the object files for tests to create the test executable
$(TEST_EXECUTABLE): $(CORE_OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# Compile the source files for core
$(OBJDIR)/core/%.o: $(COREDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Compile the source files for tests
$(OBJDIR)/test/%.o: $(TESTDIR)/cpu/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the object files
clean:
	rm -f $(CORE_OBJS) $(EMU_OBJS) $(TEST_OBJS)

# Clean and remove both executables
cleanall: clean
	rm -f $(EXECUTABLE) $(TEST_EXECUTABLE)