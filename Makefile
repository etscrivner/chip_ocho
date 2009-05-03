# chip_ocho Makefile
CXX= g++
CXXFLAGS= -O2 -W -Wall -ansi -pedantic
OBJS= chip_ocho.o memory.o
PROGRAM= chip_ocho
TESTS= memory.o tests/all_tests.o tests/lemon.o
TESTPRG= chip_ocho_tests
DISASM= memory.o disassembler/chip_disasm.o
DISASMPRG= chip_disasm
ENDIANESS= LITTLE_ENDIAN

all: $(OBJS)
	@$(CXX) -D$(ENDIANESS) -o $(PROGRAM) $(OBJS)
	@echo "Compilation complete, executable file is './chip_ocho'"
	
tests: $(TESTS)
	@$(CXX) -D$(ENDIANESS) -o $(TESTPRG) $(TESTS)
	@echo "Compiling tests complete, executable file is './chip_ocho_tests'"
	
disasm: $(DISASM)
	@$(CXX) -D$(ENDIANESS) -o $(DISASMPRG) $(DISASM)
	@echo "Compiling disassembler complete, executable file is './chip_disasm'"
	
%.o: %.cpp %.h
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *~ chip_ocho chip_ocho_tests chip_disasm *.o tests/*.o