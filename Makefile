CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g
SRC = $(wildcard src/*.c)
INCLUDE_SRC = $(wildcard include/*.c)
TEST_SRC = $(wildcard tests/*.c)
OBJ = $(patsubst src/%.c, build/obj/%.o, $(SRC))
INCLUDE_OBJ = $(patsubst include/%.c, build/obj/include/%.o, $(INCLUDE_SRC))
TEST_OBJ = $(patsubst tests/%.c, build/obj/tests/%.o, $(TEST_SRC))

BUILD_DIRS = build build/obj build/obj/include build/obj/tests

all: build/vine build/test

# Main build target
build/vine: $(OBJ) $(INCLUDE_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Test build target
build/test: $(TEST_OBJ) $(INCLUDE_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lcunit -lcrypto

# Compile source files
build/obj/%.o: src/%.c | $(BUILD_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile include files
build/obj/include/%.o: include/%.c | $(BUILD_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test files
build/obj/tests/%.o: tests/%.c | $(BUILD_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build directories exist
$(BUILD_DIRS):
	mkdir -p $@

# Clean up build files
clean:
	rm -rf build
