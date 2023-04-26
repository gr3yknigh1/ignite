#!/bin/make
# editor/Makefile
.PHONY: editor run

ifndef PROJECT_ROOT
$(error Running not from root makefile)
endif

# ifndef IGNITE_ENGINE_LIB
# $(error Including editor before engine)
# endif

unexport THIS_MAKE_FILE     := $(abspath $(lastword $(MAKEFILE_LIST)))
unexport THIS_MAKE_FILE_DIR := $(realpath $(patsubst %/,%,$(dir $(THIS_MAKE_FILE))))

unexport TARGET_DIR           := $(THIS_MAKE_FILE_DIR)
unexport TARGET_NAME          := ignite
unexport TARGET               := $(PROJECT_BUILD_DIR)/$(TARGET_NAME)

unexport TARGET_INCLUDE_DIR   := $(TARGET_DIR)/include
unexport TARGET_SOURCES_DIR   := $(TARGET_DIR)/src
# unexport TARGET_TESTS_DIR     := $(TARGET_DIR)/tests

unexport TARGET_SOURCES       := $(wildcard $(TARGET_SOURCES_DIR)/*.c)
unexport TARGET_HEADERS       := $(wildcard $(TARGET_INCLUDE_DIR)/**/*.h)
unexport TARGET_OBJS          := $(patsubst $(TARGET_SOURCES_DIR)/%.c, $(PROJECT_OBJ_DIR)/%.o, $(TARGET_SOURCES))

# TARGET_TESTS_SOURCES := $(wildcard $(TARGET_TESTS_DIR)/*.c)
# TARGET_TESTS_BINS    := $(patsubst $(TARGET_TESTS_DIR)/%.c, $(PROJECT_TESTS_BIN_DIR)/%, $(TARGET_TESTS_SOURCES))

PROJECT_INCLUDE_FLAGS := $(PROJECT_INCLUDE_FLAGS) -I$(TARGET_INCLUDE_DIR)
PROJECT_SOURCES       := $(PROJECT_SOURCES) $(TARGET_SOURCES)
PROJECT_HEADERS       := $(PROJECT_HEADERS) $(TARGET_HEADERS)
PROJECT_TARGETS       := $(PROJECT_TARGETS) $(TARGET)

editor: $(TARGET)

$(TARGET): $(IGNITE_ENGINE_LIB) $(TARGET_OBJS)
	$(RM) $@
	$(CC) $(CFLAGS) $(CFLAGS_SECURE) $^ -o $@

$(PROJECT_OBJ_DIR)/%.o: $(TARGET_SOURCES_DIR)/%.c $(TARGET_INCLUDE_DIR)/$(PROJECT_NAME)/%.h
	$(CC) $(CFLAGS) $(CFLAGS_SECURE) -c $< -o $@ $(PROJECT_INCLUDE_FLAGS)

$(PROJECT_OBJ_DIR)/%.o: $(TARGET_SOURCES_DIR)/%.c
	$(CC) $(CFLAGS) $(CFLAGS_SECURE) -c $< -o $@ $(PROJECT_INCLUDE_FLAGS)

# tests: $(EXEC) $(TESTS_BIN_DIR) $(TESTS_BINS)
# 	@for test in $(TESTS_BINS); do $$test --verbose=1 ; done
#
# $(TESTS_BIN_DIR)/%: $(TESTS_DIR)/%.c
# 	$(CC) $(CFLAGS) $< $(TARGET_OBJS) -o $@ -lcriterion $(INCLUDE_FLAGS)

run: $(TARGET)
	$<
