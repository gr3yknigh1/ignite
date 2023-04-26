.PHONY: configure compiledb-clean

RM ?= rm -rf

THIS_MAKE_FILE     := $(abspath $(lastword $(MAKEFILE_LIST)))
THIS_MAKE_FILE_DIR := $(realpath $(patsubst %/,%,$(dir $(THIS_MAKE_FILE))))
PROJECT_ROOT       ?= $(THIS_MAKE_FILE_DIR)

PY_COMP_DB       := compiledb
PY_ENV           := $(PROJECT_ROOT)/.env
PY_ENV_BIN       := $(PY_ENV)/bin
PY_PIP_EXEC      := $(PY_ENV_BIN)/pip
PY_COMP_DB_EXEC  := $(PY_ENV_BIN)/compiledb
COMPILE_COMMANDS := $(PROJECT_ROOT)/compile_commands.json

$(PY_COMP_DB_EXEC):
	python -m venv $(PY_ENV)
	$(PY_PIP_EXEC) install $(PY_COMP_DB)

$(COMPILE_COMMANDS): $(PY_COMP_DB_EXEC)
	$< make all tests -o $@
	$< make clean checks -o $@

configure: $(COMPILE_COMMANDS)

compiledb-clean:
	$(RM) $(PY_ENV)
	$(RM) $(COMPILE_COMMANDS)
