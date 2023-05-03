.PHONY: configure reconfigure compiledb-clean compiledb-clean-env compiledb-clean-compile-commands

RM ?= rm -rf

unexport THIS_MAKE_FILE     := $(abspath $(lastword $(MAKEFILE_LIST)))
unexport THIS_MAKE_FILE_DIR := $(realpath $(patsubst %/,%,$(dir $(THIS_MAKE_FILE))))
unexport PROJECT_ROOT       ?= $(THIS_MAKE_FILE_DIR)

unexport PY_COMP_DB       := compiledb
unexport PY_ENV           := $(PROJECT_ROOT)/.env
unexport PY_ENV_BIN       := $(PY_ENV)/bin
unexport PY_PIP_EXEC      := $(PY_ENV_BIN)/pip
unexport PY_COMP_DB_EXEC  := $(PY_ENV_BIN)/compiledb

export COMPILE_COMMANDS := $(PROJECT_ROOT)/compile_commands.json

$(PY_COMP_DB_EXEC):
	python -m venv $(PY_ENV)
	$(PY_PIP_EXEC) install $(PY_COMP_DB)

$(COMPILE_COMMANDS): $(PY_COMP_DB_EXEC)
	$< make clean all -o $@
	$< make clean checks -o $@

configure: $(COMPILE_COMMANDS)

reconfigure: compiledb-clean-compile-commands configure

compiledb-clean-env:
	$(RM) $(PY_ENV)

compiledb-clean-compile-commands:
	$(RM) $(COMPILE_COMMANDS)

compiledb-clean: compiledb-clean-env compiledb-clean-compile-commands
