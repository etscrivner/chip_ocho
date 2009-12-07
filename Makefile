# chip_ocho Makefile
#
# Time-stamp: <Last modified 2009-12-06 19:51:29 by Eric Scrivner>
CXX= g++
CXXFLAGS= -O2 -W -Wall -ansi -pedantic
OBJS= chip_ocho.o memory.o video.o cpu.o
PROGRAM= chip_ocho

# Unit tests
TESTS= memory.o tests/all_tests.o tests/lemon.o
TESTPRG= chip_ocho_tests

# Disassembler
DISASM= memory.o disassembler/chip_disasm.o
DISASMPRG= chip_disasm

# Machine endianess
ENDIANESS= LITTLE_ENDIAN

# OpenGL
SHELL = /bin/sh
OS = $(shell uname -s)
$(info OS=${OS})

INCS = -I/opt/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE
ifeq (${OS}, Darwin)
LIBS = -lSDLmain -lSDL -framework OpenGL -framework GLUT -framework Cocoa
else
LIBS = -lGL -lglut -lGLU
endif

all: $(OBJS)
	@$(CXX) $(INCS) $(LIBS) -D$(ENDIANESS) -o $(PROGRAM) $(OBJS)
	@echo "Compilation complete, executable file is './chip_ocho'"

tests: $(TESTS)
	@$(CXX) -D$(ENDIANESS) -o $(TESTPRG) $(TESTS)
	@echo "Compiling tests complete, executable file is './chip_ocho_tests'"

disasm: $(DISASM)
	@$(CXX) -D$(ENDIANESS) -o $(DISASMPRG) $(DISASM)
	@echo "Compiling disassembler complete, executable file is './chip_disasm'"

%.o: %.cpp %.h
	@echo "Compiling $<"
	@$(CXX) $(INCS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *~ chip_ocho chip_ocho_tests chip_disasm *.o tests/*.o