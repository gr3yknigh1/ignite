.PHONY: default all dirs debug release asan lsan msan ubsan tests clean veryclean clean-build clean-tests

MD = mkdir -p
RM = rm -rf

THIS_MAKE_FILE     := $(abspath $(lastword $(MAKEFILE_LIST)))
THIS_MAKE_FILE_DIR := $(realpath $(patsubst %/,%,$(dir $(THIS_MAKE_FILE))))

export PROJECT_ROOT           := $(THIS_MAKE_FILE_DIR)
export PROJECT_NAME           := ignite
export PROJECT_BUILD_DIR      := $(PROJECT_ROOT)/build
export PROJECT_OBJ_DIR        := $(PROJECT_BUILD_DIR)/objs
export PROJECT_TESTS_EXEC_DIR := $(PROJECT_BUILD_DIR)/tests

export PROJECT_SOURCES       =
export PROJECT_HEADERS       =
export PROJECT_TESTS_SOURCES =
export PROJECT_OBJS          =

export PROJECT_TARGETS       =
export PROJECT_TESTS_EXECS   =

export CC            := clang
export CFLAGS        := -std=c2x
export CFLAGS_SECURE := -Wall
export AR            := ar
export ARFLAGS       := -cvrs

CFLAGS_SECURE += -Werror
CFLAGS_SECURE += -Wextra
CFLAGS_SECURE += -Wpedantic
CFLAGS_SECURE += -Wuninitialized
CFLAGS_SECURE += -Wmissing-include-dirs
CFLAGS_SECURE += -Wshadow
CFLAGS_SECURE += -Wundef
CFLAGS_SECURE += -Warc-repeated-use-of-weak
CFLAGS_SECURE += -Wbitfield-enum-conversion
CFLAGS_SECURE += -Wconditional-uninitialized
CFLAGS_SECURE += -Wthread-safety
CFLAGS_SECURE += -Wconversion
CFLAGS_SECURE += -Wswitch -Wswitch-enum
CFLAGS_SECURE += -Wformat-security
CFLAGS_SECURE += -Wdouble-promotion
CFLAGS_SECURE += -Wfloat-equal
CFLAGS_SECURE += -Wfloat-overflow-conversion
CFLAGS_SECURE += -Wfloat-zero-conversion
CFLAGS_SECURE += -Wsign-compare
CFLAGS_SECURE += -Wsign-conversion

export DEBUG_MACRO   := IGNITE_CONFIG_DEBUG
export RELEASE_MACRO := IGNITE_CONFIG_RELEASE

default: all

include $(PROJECT_ROOT)/thirdparty/glad/Makefile

include $(PROJECT_ROOT)/ignite-engine/Makefile
include $(PROJECT_ROOT)/ignite-editor/Makefile

include $(PROJECT_ROOT)/make/compiledb.mk
include $(PROJECT_ROOT)/make/checks.mk
include $(PROJECT_ROOT)/make/format.mk

all: dirs debug
dirs: $(PROJECT_BUILD_DIR) $(PROJECT_OBJ_DIR) $(PROJECT_TESTS_EXEC_DIR)

debug: CFLAGS += -g -O0 -D $(DEBUG_MACRO)
debug: $(PROJECT_TARGETS)

release: CFLAGS += -O3 -D $(RELEASE_MACRO)
release: clean
release: $(PROJECT_TARGETS)

asan: CFLAGS += -fsanitize=address -fno-optimize-sibling-calls -fno-omit-frame-pointer
asan: debug

lsan: CFLAGS += -fsanitize=leak
lsan: debug

msan: CFLAGS += -fsanitize=memory -fno-optimize-sibling-calls -fno-omit-frame-pointer
msan: debug

ubsan: CFLAGS += -fsanitize=undefined
ubsan: debug

tests: $(PROJECT_TESTS_EXECS)
	for test in $(PROJECT_TESTS_EXECS); do $$test --verbose=1 ; done

clean:
	for obj in $(PROJECT_OBJS); do $(RM) $$obj ; done

clean-tests:
	$(RM) $(PROJECT_TESTS_EXEC_DIR)

clean-build:
	$(RM) $(PROJECT_BUILD_DIR)

veryclean: clean-build compiledb-clean

reset: veryclean configure clean all

$(PROJECT_BUILD_DIR):
	$(MD) $@

$(PROJECT_OBJ_DIR):
	$(MD) $@

$(PROJECT_TESTS_EXEC_DIR):
	$(MD) $@

