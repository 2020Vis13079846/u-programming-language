# Makefile

# U information

AUTHOR      = Simon Chaykin
LICENSE     = MIT

# Makefile configuration

BUILD_DIR   = build
Q           = @
DIRECTORIES = $(BUILD_DIR)

# Files

BINFILE     = ulang

# Compilers

CC          = gcc

# Compilers' flags

CFLAGS      = -std=c89 -Wall -Wextra -Werror -pedantic-errors

# Sources

SOURCES    += $(shell find . -name "*.c" -print -type f)
OBJS       := $(patsubst %.c, %.o, $(SOURCES))

all: clean directories $(BINFILE) test

directories:
	$(Q) mkdir -p $(patsubst %,"./%",$(DIRECTORIES))

$(BINFILE): $(OBJS)
	$(Q) $(CC) $(patsubst ./%.o,$(BUILD_DIR)/%.o,$(OBJS)) -o $(BUILD_DIR)/$(BINFILE) $(CFLAGS)

test:
	$(Q) $(BUILD_DIR)/$(BINFILE)

clean:
	@rm -rf $(DIRECTORIES) $(patsubst %.o,$(BUILD_DIR)/%.o,$(OBJS))

# Compilation

%.o: %.c
	$(Q) $(CC) -c $< -o $(BUILD_DIR)/$@ $(CFLAGS)
