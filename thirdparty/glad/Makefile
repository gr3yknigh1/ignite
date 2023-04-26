.PHONY: glad

ifndef PROJECT_ROOT
$(error Running not from root makefile)
endif

THIS_MAKE_FILE     := $(abspath $(lastword $(MAKEFILE_LIST)))
THIS_MAKE_FILE_DIR := $(realpath $(patsubst %/,%,$(dir $(THIS_MAKE_FILE))))

GLAD_DIR  := $(THIS_MAKE_FILE_DIR)
GLAD_NAME := glad
export GLAD_LIB  := $(PROJECT_BUILD_DIR)/lib$(GLAD_NAME).a

GLAD_INCLUDE_DIR := $(GLAD_DIR)/include
GLAD_SOURCES_DIR := $(GLAD_DIR)/src

GLAD_SOURCES := $(wildcard $(GLAD_SOURCES_DIR)/*.c)
GLAD_HEADERS := $(wildcard $(GLAD_INCLUDE_DIR)/**/*.h)
GLAD_OBJS    := $(patsubst $(GLAD_SOURCES_DIR)/%.c, $(PROJECT_OBJ_DIR)/%.o, $(GLAD_SOURCES))

# PROJECT_INCLUDE_FLAGS := $(PROJECT_INCLUDE_FLAGS) -I$(GLAD_INCLUDE_DIR)
PROJECT_TARGETS       := $(PROJECT_GLADS) $(GLAD)

export GLAD_INCLUDE := $(GLAD_INCLUDE_DIR)

glad: $(GLAD_LIB)

$(GLAD_LIB): $(GLAD_OBJS)
	$(RM) $@
	$(AR) $(ARFLAGS) $@ $^

$(PROJECT_OBJ_DIR)/%.o: $(GLAD_SOURCES_DIR)/%.c $(GLAD_INCLUDE_DIR)/$(GLAD_NAME)/%.h
	$(CC) $(CFLAGS) -I $(GLAD_INCLUDE_DIR) -c $< -o $@

$(PROJECT_OBJ_DIR)/%.o: $(GLAD_SOURCES_DIR)/%.c
	$(CC) $(CFLAGS) -I $(GLAD_INCLUDE_DIR) -c $< -o $@
