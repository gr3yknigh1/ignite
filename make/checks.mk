.PHONY: checks

unexport THIS_MAKE_FILE     := $(abspath $(lastword $(MAKEFILE_LIST)))
unexport THIS_MAKE_FILE_DIR := $(realpath $(patsubst %/,%,$(dir $(THIS_MAKE_FILE))))
unexport PROJECT_ROOT       ?= $(THIS_MAKE_FILE_DIR)

ifndef PROJECT_SOURCES
$(error `PROJECT_SOURCES` (list of all source files) not found)
endif

ifndef PROJECT_HEADERS
$(error `PROJECT_HEADERS` (list of all header files) not found)
endif

export COMPILE_COMMANDS   ?= $(PROJECT_ROOT)/compile_commands.json

unexport CLANG_TIDY       := clang-tidy
unexport CLANG_TIDY_FLAGS := -p $(COMPILE_COMMANDS) --config-file="$(PROJECT_ROOT)/.clang-tidy" -header-filter=.* --use-color --warnings-as-errors=*

checks:
	$(CLANG_TIDY) $(PROJECT_SOURCES) $(CLANG_TIDY_FLAGS) || true
	$(CLANG_TIDY) $(PROJECT_HEADERS) $(CLANG_TIDY_FLAGS) || true

