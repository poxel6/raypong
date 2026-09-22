CC=clang
OLVL=2

CFLAGS  = -std=c23 -I. -Iinclude
LDFLAGS = -Lvendor
LDLIBS  = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

BIN = game

DEBUG_DIR = build/debug
DEBUG_OBJ_DIR = $(DEBUG_DIR)/objects
DEBUG_BIN = $(DEBUG_DIR)/$(BIN)

RELEASE_DIR = build/release
RELEASE_OBJ_DIR = $(RELEASE_DIR)/objects
RELEASE_BIN = $(RELEASE_DIR)/$(BIN)

DEBUG_CFLAGS = $(CFLAGS) -O0 -g
RELEASE_CFLAGS = $(CFLAGS) -O$(OLVL) -DNDEBUG

DEBUG_OBJS = \
	$(DEBUG_OBJ_DIR)/main.o \
	$(DEBUG_OBJ_DIR)/paddle.o \
	$(DEBUG_OBJ_DIR)/ball.o \
	$(DEBUG_OBJ_DIR)/bricks.o

RELEASE_OBJS = \
	$(RELEASE_OBJ_DIR)/main.o \
	$(RELEASE_OBJ_DIR)/paddle.o \
	$(RELEASE_OBJ_DIR)/ball.o \
	$(RELEASE_OBJ_DIR)/bricks.o

.PHONY: all debug run release clean

all: run

debug: $(DEBUG_BIN)

run: debug
	./$(DEBUG_BIN)

release: $(RELEASE_BIN)

$(DEBUG_BIN): $(DEBUG_OBJS)
	@mkdir -p $(@D)
	$(CC) $(DEBUG_OBJS) $(LDFLAGS) $(LDLIBS) -o $@

$(RELEASE_BIN): $(RELEASE_OBJS)
	@mkdir -p $(@D)
	$(CC) $(RELEASE_OBJS) $(LDFLAGS) $(LDLIBS) -o $@

DEBUG_DEPS = $(DEBUG_OBJS:.o=.d)
RELEASE_DEPS = $(RELEASE_OBJS:.o=.d)

-include $(DEBUG_DEPS) $(RELEASE_DEPS)

$(DEBUG_OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(DEBUG_CFLAGS) -MMD -MP -c $< -o $@

$(RELEASE_OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(RELEASE_CFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -rf build
