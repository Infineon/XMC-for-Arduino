
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
	export RULE_TEXTS=$(CONFIG_DIR)/cppcheck/misra.txt
	$(CPPCHECK_PATH)/build/bin/cppcheck -i build -i examples -i test \
										-I$(C_CPP_SOURCES) \
	 	                                --checkers-report=cppcheck.checkers --check-level=exhaustive --xml --enable=all --inconclusive \
	                                    --addon=$(CONFIG_DIR)/cppcheck/misra_local.py --addon=misc \
	                                    --max-configs=100 ./ 2> ./err.xml
	$(CPPCHECK_PATH)/htmlreport/cppcheck-htmlreport --file=err.xml --title=TLx493D --report-dir=cppcheck_reports --source-dir=.
	firefox cppcheck_reports/index.html

