# chip_ocho Makefile
CXX	= g++
CXXFLAGS= -O2 -W -Wall -ansi -pedantic
OBJS = chip_ocho.o memory.o
PROGRAM = chip_ocho

all: $(OBJS)
	@$(CXX) -o $(PROGRAM) $(OBJS) $(TESTS)
	@echo "Compilation complete, executable file is './chip_ocho'"
	
%.o: %.cpp %.h
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *~ *.o tests/*.o