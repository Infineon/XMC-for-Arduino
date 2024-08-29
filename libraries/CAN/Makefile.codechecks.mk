
WIN_USER ?=



#################################### clang-format code formatter
### Need to install clang-tidy
### You may want to copy the config to your working directory to use the common settings.
### cp config/clang-format/.clang-format .

clang-format:
	clang-format -i $(shell find src -name CAN\*.[hc]pp\*)



#################################### clang-tidy static code checker  //TODO: how to implement this for core library?
### Need to install clang-tidy

clang-tidy-test: C_CPP_SOURCES = $(shell find test -name \*.[hc]pp\*)
clang-tidy-src:  C_CPP_SOURCES = $(shell find src -name \*.[hc]pp\*)

clang-tidy-test clang-tidy-src : clang-tidy

clang-tidy:
ifeq ($(WIN_USER),)
	$(warn "Must set variable WIN_USER in order to include XMCLib files in clang-tidy analysis !")
	clang-tidy --config-file=../../config/clang-tidy/.clang-tidy -header-filter=. --extra-arg="-Isrc/framework/arduino" --extra-arg="-Itest/unit/src/framework/arduino/corelibs" $(C_CPP_SOURCES) --
else
	$(info $(C_CPP_SOURCES))
	clang-tidy --config-file=../../config/clang-tidy/.clang-tidy -header-filter=. --extra-arg="-Isrc/framework/arduino" --extra-arg="-Itest/unit/src/framework/arduino/corelibs" --extra-arg="-I/mnt/c/Users/$(WIN_USER)/AppData/Local/Arduino15/packages/Infineon/hardware/xmc/3.1.0/cores" $(C_CPP_SOURCES) --
endif



#################################### scan-build static code checker
### Need to install scan-build
### After executing the scan-build target run the command scan-view as printed in the scan-build output last line.
### Or use firefox directly.
scan-build:
	scan-build -o scan-build-reports make -f Makefile.codechecks.mk foo
#	firefox scan-build-reports/

foo:
	$(CC) -c -Wextra -Wall -Wfloat-equal -Wconversion -Wredundant-decls -Wswitch-default -Wdouble-promotion -Wpedantic -Wunreachable-code -std=c++20 config/sca/foo.cpp -o foo.o



#################################### cppcheck static code checker
### Requirement : install cppcheck from https://github.com/danmar/cppcheck
cppcheck: C_CPP_SOURCES = ./config/sca

CPPCHECK_PATH = ~/cppcheck/cppcheck.danmar

cppcheck:
	export RULE_TEXTS=config/cppcheck/misra.txt
	$(CPPCHECK_PATH)/cppcheck -i build -i doc -i examples -i results -i reports_hml -i src -i test \
	                                    -I$(C_CPP_SOURCES) \
	 	                                --checkers-report=cppcheck.checkers --check-level=exhaustive --xml --enable=all --inconclusive \
	                                    --addon=config/cppcheck/misra_local.py --addon=misc \
	                                    --max-configs=100 ./ 2> ./err.xml
	$(CPPCHECK_PATH)/htmlreport/cppcheck-htmlreport --file=err.xml --title=TLx493D --report-dir=cppcheck_reports --source-dir=.
	firefox cppcheck_reports/index.html

