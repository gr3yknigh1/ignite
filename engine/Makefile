.PHONY: engine

ifndef PROJECT_ROOT
$(error Running not from root makefile)
endif

unexport THIS_MAKE_FILE     := $(abspath $(lastword $(MAKEFILE_LIST)))
unexport THIS_MAKE_FILE_DIR := $(realpath $(patsubst %/,%,$(dir $(THIS_MAKE_FILE))))

unexport TARGET_DIR         := $(THIS_MAKE_FILE_DIR)
unexport TARGET_NAME        := libignite.a
unexport TARGET             := $(PROJECT_BUILD_DIR)/$(TARGET_NAME)

unexport TARGET_INCLUDE_DIR := $(TARGET_DIR)/include
unexport TARGET_SOURCES_DIR := $(TARGET_DIR)/src
unexport TARGET_TESTS_DIR   := $(TARGET_DIR)/tests

unexport TARGET_SOURCES     := $(wildcard $(TARGET_SOURCES_DIR)/*.c)
unexport TARGET_HEADERS     := $(wildcard $(TARGET_INCLUDE_DIR)/**/*.h)
unexport TARGET_OBJS        := $(patsubst $(TARGET_SOURCES_DIR)/%.c, $(PROJECT_OBJ_DIR)/%.o, $(TARGET_SOURCES))

unexport TARGET_TESTS_SOURCES := $(wildcard $(TARGET_TESTS_DIR)/*.c)
unexport TARGET_TESTS_EXECS   := $(patsubst $(TARGET_TESTS_DIR)/%.c, $(PROJECT_TESTS_EXEC_DIR)/%, $(TARGET_TESTS_SOURCES))

PROJECT_INCLUDE_FLAGS := $(PROJECT_INCLUDE_FLAGS) -I$(TARGET_INCLUDE_DIR)
PROJECT_SOURCES       := $(PROJECT_SOURCES) $(TARGET_SOURCES)
PROJECT_HEADERS       := $(PROJECT_HEADERS) $(TARGET_HEADERS)
PROJECT_TESTS_EXECS   := $(PROJECT_TESTS_EXECS) $(TARGET_TESTS_EXECS)
PROJECT_TARGETS       := $(PROJECT_TARGETS) $(TARGET)

export IGNITE_ENGINE_LIB := $(TARGET)

engine: $(TARGET)

$(TARGET): $(TARGET_OBJS)
	$(RM) $@
	$(AR) $(ARFLAGS) $@ $^

$(PROJECT_OBJ_DIR)/%.o: $(TARGET_SOURCES_DIR)/%.c $(TARGET_INCLUDE_DIR)/$(PROJECT_NAME)/%.h
	$(CC) $(CFLAGS) $(CFLAGS_SECURE) -c $< -o $@ $(PROJECT_INCLUDE_FLAGS)

$(PROJECT_OBJ_DIR)/%.o: $(TARGET_SOURCES_DIR)/%.c
	$(CC) $(CFLAGS) $(CFLAGS_SECURE) -c $< -o $@ $(PROJECT_INCLUDE_FLAGS)

$(PROJECT_TESTS_EXEC_DIR)/%: $(TARGET_OBJS) $(TARGET_TESTS_DIR)/%.c
	$(CC) $(CFLAGS) $^ -o $@ -lcriterion $(PROJECT_INCLUDE_FLAGS)

