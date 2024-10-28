
WIN_USER ?=
CONFIG_DIR := ../../config
CORE_LIB_DIR := ../../cores


CLANG_FORMAT_DIR := $(CONFIG_DIR)/clang-format
CLANG_TIDY_DIR := $(CONFIG_DIR)/clang-tidy


#################################### clang-format code formatter
### Need to install clang-tidy

clang-format:

	clang-format -i -style=file:$(CLANG_FORMAT_DIR)/.clang-format $(shell find src -name \*.[hc]\*)



##TODO: add compilation database for builtin libraries!
#################################### clang-tidy static code checker  

clang-tidy-test: C_CPP_SOURCES = $(shell find test -name \*.[hc]\*)
clang-tidy-src:  C_CPP_SOURCES = $(shell find src -name \*.[hc]\*)

clang-tidy-test clang-tidy-src : clang-tidy

clang-tidy:
	$(info $(C_CPP_SOURCES))
	clang-tidy $(C_CPP_SOURCES) --config-file=$(CLANG_TIDY_DIR)/.clang-tidy -header-filter='' -- -Isrc/framework/arduino -Itest/unit/src/framework/arduino/corelibs -I$(CORE_LIB_DIR) > clang-tidy-report.txt	



#################################### scan-build static code checker  #TODO: still using foo example
### After executing the scan-build target run the command scan-view as printed in the scan-build output last line.
### Or use firefox directly.
scan-build:
	scan-build -o scan-build-reports make -f Makefile.codechecks.mk foo
	firefox scan-build-reports/

foo:
	$(CC) -c -Wextra -Wall -Wfloat-equal -Wconversion -Wredundant-decls -Wswitch-default -Wdouble-promotion -Wpedantic -Wunreachable-code -std=c++20 $(CONFIG_DIR)/sca/foo.cpp -o foo.o



#################################### cppcheck static code checker 
### Requirement : install cppcheck from https://github.com/danmar/cppcheck
cppcheck: C_CPP_SOURCES = ./src

CPPCHECK_PATH = ~/cppcheck/cppcheck

cppcheck:
	$(CPPCHECK_PATH)/cppcheck -I $(C_CPP_SOURCES) \
	                          -i build -i doc -i examples -i results -i reports_hml -i src -i test $(C_CPP_SOURCES) \
	                          --check-level=exhaustive --enable=all --inconclusive \
	                          --addon=config/cppcheck/misra.json --addon=misc --std=c++20 \
	                          --checkers-report=cppcheck.checkers --xml --max-configs=50 2> ./err.xml
	$(CPPCHECK_PATH)/htmlreport/cppcheck-htmlreport --file=err.xml --title=TestCPPCheck --report-dir=cppcheck-reports --source-dir=.
	firefox cppcheck-reports/index.html

