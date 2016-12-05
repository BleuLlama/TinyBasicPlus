#
# makefile for command line TinyBasicPlus
# (basic input version)
#
#  requires GCC tools
#
#  tested on OS X, MinGW
#  (we will autoconfigure for the right platform)


########################################
export ARCH := $(shell uname)
ifeq ($(ARCH),MINGW32_NT-5.1)
  # Win XP
  export ARCH := MINGW
endif
ifeq ($(ARCH),MINGW32_NT-5.2)
  # Server 2003
  export ARCH := MINGW
endif
ifeq ($(ARCH),MINGW32_NT-6.1)
  # Windows 7
  export ARCH := MINGW
endif

# mingw will be: MINGW
# os x will be: Darwin


ifeq ($(ARCH),MINGW)
export EXEEXT := .exe
else
export EXEEXT := 
endif

export CXXFLAGS += -DFORCE_DESKTOP -Wno-int-to-pointer-cast

export CXX := g++
export CC  := gcc

########################################
PROG := tbp$(EXEEXT)

SRCS := TinyBasicPlus.cpp \
        main.cpp

OBJS := $(SRCS:%.cpp=%.o)

all: $(PROG)

$(PROG): TinyBasicPlus.o main.o
	@echo link $@
	@$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) $(LIBS) -o $@


TinyBasicPlus.cpp: ../Arduino/TinyBasicPlus.ino
	@echo copy $< to $@
	@cp $< $@

%.o: %.cpp
	@echo compile $<
	@$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ $<

clean:
	@echo removing generated files
	@-rm -f $(OBJS) $(PROG) TinyBasicPlus.cpp
.PHONY: clean

test: $(PROG)
	./$(PROG)
.PHONY: test
