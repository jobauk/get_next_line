# Compiler
CC := cc
CFLAGS := -Wall -Wextra -Werror -pedantic

# Compiler debug
LD_FLAGS := -fsanitize=undefined
DEBUG_CFLAGS := $(CFLAGS) \
	-g3 -O0 -fno-omit-frame-pointer \
	-fstrict-aliasing -Wcast-align \
	-Wconversion -Wsign-conversion \
	-Wshadow -Wundef \
	$(LD_FLAGS)

OUTDIR := target

# Source
SRCS := get_next_line.c get_next_line_utils.c
OBJS := $(SRCS:%.c=$(OUTDIR)/%.o)

DEBUG_OBJS := $(SRCS:%.c=$(OUTDIR)/%.o)

TEST_SRCS := $(wildcard .tests/*.c)
TEST_OBJS := $(TEST_SRCS:.tests/%.c=$(OUTDIR)/tests/%.o)

# Output
TEST_BIN := $(OUTDIR)/test
DEBUG_BIN := $(OUTDIR)/debug

# Debugger
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	DEBUGGER := lldb
else
	DEBUGGER := gdb
endif

# Criterion
CRITERION_CFLAGS := $(shell pkg-config --cflags criterion)
CRITERION_LIBS := $(shell pkg-config --libs criterion)

# Default
all: $(DEBUG_BIN)

# Utility commands
test: $(TEST_BIN)
	@./$(TEST_BIN) $(if $(FILTER),--filter "$(FILTER)")

run: $(DEBUG_BIN)
	@./$(DEBUG_BIN)

debug: $(DEBUG_BIN)
	@$(DEBUGGER) $(DEBUG_BIN)

build: $(DEBUG_BIN)

$(OUTDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(DEBUG_CFLAGS) -c $< -o $@

$(OUTDIR)/tests/%.o: .tests/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(DEBUG_CFLAGS) $(CRITERION_CFLAGS) -c $< -o $@

$(TEST_BIN): $(DEBUG_OBJS) $(TEST_OBJS)
	@$(CC) $(LD_FLAGS) $^ $(CRITERION_LIBS) -o $@

$(DEBUG_BIN): $(DEBUG_OBJS)
	@$(CC) $(LD_FLAGS) $^ -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(TEST_BIN) $(DEBUG_BIN)

re: fclean all
