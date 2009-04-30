# chip_ocho Makefile
CXX= g++
CXXFLAGS= -O2 -W -Wall -ansi -pedantic
OBJS= chip_ocho.o memory.o
PROGRAM= chip_ocho
TESTS= memory.o tests/all_tests.o tests/lemon.o
TESTPRG= chip_ocho_tests

all: $(OBJS)
	@$(CXX) -o $(PROGRAM) $(OBJS)
	@echo "Compilation complete, executable file is './chip_ocho'"
	
tests: $(TESTS)
	@$(CXX) -o $(TESTPRG) $(TESTS)
	@echo "Compiling tests complete, executable file is './chip_ocho_tests'"
	
%.o: %.cpp %.h
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *~ chip_ocho *.o tests/*.o