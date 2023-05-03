.PHONY: format

ifndef PROJECT_SOURCES
$(error `PROJECT_SOURCES` (list of all source files) not found)
endif

ifndef PROJECT_HEADERS
$(error `PROJECT_HEADERS` (list of all header files) not found)
endif

ifndef PROJECT_TESTS_SOURCES
$(error `PROJECT_TESTS_SOURCES` (list of all test's source files) not found)
endif

unexport CLANG_FMT        := clang-format
unexport CLANG_FMT_FLAGS  := -i

format:
	$(CLANG_FMT) $(CLANG_FMT_FLAGS) $(PROJECT_SOURCES)
	$(CLANG_FMT) $(CLANG_FMT_FLAGS) $(PROJECT_HEADERS)
	$(CLANG_FMT) $(CLANG_FMT_FLAGS) $(PROJECT_TESTS_SOURCES)

