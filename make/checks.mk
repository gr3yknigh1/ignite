THIS_MAKE_FILE     := $(abspath $(lastword $(MAKEFILE_LIST)))
THIS_MAKE_FILE_DIR := $(realpath $(patsubst %/,%,$(dir $(THIS_MAKE_FILE))))
PROJECT_ROOT   ?= $(THIS_MAKE_FILE_DIR)

COMPILE_COMMANDS ?= $(PROJECT_ROOT)/compile_commands.json

ifndef PROJECT_SOURCES
$(error Running not from root makefile)
endif

ifndef PROJECT_HEADERS
$(error Running not from root makefile)
endif

CLANG_TIDY       := clang-tidy
CLANG_TIDY_FLAGS := -p $(COMPILE_COMMANDS) --config-file="$(PROJECT_ROOT)/.clang-tidy" -header-filter=.* --use-color --warnings-as-errors=*

checks:
	$(CLANG_TIDY) $(PROJECT_SOURCES) $(CLANG_TIDY_FLAGS) || true
	$(CLANG_TIDY) $(PROJECT_HEADERS) $(CLANG_TIDY_FLAGS) || true

