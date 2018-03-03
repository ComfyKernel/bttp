# Tell it to use a real shell #
SHELL=/bin/bash

# Set up paths #
ORIGIN  = $(shell readlink -f .)
BUILD   = $(ORIGIN)/build
INCLUDE = $(ORIGIN)/include
SOURCE  = $(ORIGIN)/source
TEST    = $(ORIGIN)/test

# Choose the used libraries #
# And set the compile flags #
LIBS    = -lGL -lGLEW -lglfw

CFLAGS  = -Wall -Wextra -g $(LIBS) -I $(INCLUDE)
CCFLAGS = $(CFLAGS) -std=c++17
AFLAGS  = -rvs

# Set the compilers to GCC and G++ #
C  = /usr/bin/gcc $(CFLAGS)
CC = /usr/bin/g++ $(CCFLAGS)
AR = /usr/bin/ar

# Set output name #
O = libbttp.a

# Use one of them #
CP = $(CC)
CN = "CC"

# Set file type to look for #
FT = .cpp

# Generic variables #
ACTIVITY = 0 # Check if something changed

# Get files #
FILES = $(shell find $(SOURCE) -name *$(FT))
OBJS  = $(patsubst %$(FT), %.o, $(FILES))

all: info $(BUILD)/$(O) check
	@[ $(ACTIVITY) -eq 0 ] && echo -en "[\e[34mBUILD\e[0m] Nothing to do\n" || echo -en ""
	@echo -en "[\e[34;1mBUILD\e[0m] Exiting\n"

info:
	@echo -en "[\e[32;1mINFO\e[0m]  [--Build & OS Info--]\n"
	@echo -en "[\e[32;1mINFO\e[0m]  Compiler         :" $(CP) "\n"
	@echo -en "[\e[32;1mINFO\e[0m]  Compiler Version : "
	@$CP -dumpversion
	@echo -en "[\e[32;1mINFO\e[0m]  Archive          :" $(AR) "\n"
	@echo -en "[\e[32;1mINFO\e[0m]  OS               :" $(shell uname -a)
	@echo -en "\n"
	@echo -en "[\e[32;1mINFO\e[0m]  Architecture     :" $(shell uname -m) "\n\n"

	@echo -en "[\e[32;1mINFO\e[0m]  [--Directory Info--]\n"
	@echo -en "[\e[32;1mINFO\e[0m]  Origin  :" $(ORIGIN)  "\n"
	@echo -en "[\e[32;1mINFO\e[0m]  Build   :" $(BUILD)   "\n"
	@echo -en "[\e[32;1mINFO\e[0m]  Include :" $(INCLUDE) "\n"
	@echo -en "[\e[32;1mINFO\e[0m]  Source  :" $(SOURCE)  "\n\n"

	@echo -en "[\e[34;1mBUILD\e[0m] Starting Build\n\n"

%.o: %$(FT)
	@echo -en "[\e[36;1m"$(CN)"\e[0m] -c" $^ "-o" $@ "\n"
	@$(CP) -c $^ -o $@

$(BUILD)/$(O): $(OBJS)
	$(eval ACTIVITY = 1)
	@echo -en "\n[\e[31;1mAR\e[0m]" $(AFLAGS) $@ $^ "\n"

	@[ -f $@ ] && rm $@ || echo -en ""

	@$(AR) $(AFLAGS) $@ $^

check:
	@echo -en "[\e[31;1mAR\e[0m] Checking contents of archive\n"
	@$(AR) -t $(BUILD)/$(O)

	@echo -en "\n"

clean:
	@echo -en "[\e[32;1mINFO\e[0m] Cleaning up\n"
	@echo -en "[\e[32;1mINFO\e[0m] Removing object files\n"
	@rm -v $(patsubst %.cpp, %.o, $(FILES))

	@echo -en "[\e[32;1mINFO\e[0m] Removing archive\n"
	@rm -v $(BUILD)/$(O)

# Testing Targets #

test: $(BUILD)/tester PHONY

runtest:
	@cd $(BUILD); \
	./tester;

$(BUILD)/tester: $(TEST)/test.o PHONY
	@echo -en "[\e[33;1mTEST\e[0m] Building Test\n"
	@echo -en "[\e[36;1m"$(CN)"\e[0m]" $< "-o" $@ "\n"

	@$(CP) $< -o $@ -L$(BUILD) -lbttp

PHONY:
