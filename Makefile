SRC = $(wildcard *.cpp) $(wildcard commands/*.cpp)
TESTSRC = $(wildcard tests/*.cpp) $(wildcard commands/*.cpp) $(wildcard tests/fakes/*.cpp)  $(wildcard tests/util/*.cpp) command_factory.cpp os_environment.cpp command_parser.cpp cli.cpp ofstream_extended.cpp
TESTDEFINE = -DTEST
BINDIR = bin

# Build the main program to bin/main
ash: $(SRC) $(BINDIR)
	g++ $(SRC) -o $(BINDIR)/ash

# Build the test program to bin/test
test: $(TESTSRC)
	g++ $(TESTSRC) -o $(BINDIR)/test $(TESTDEFINE) -pthread

# Build the bin directory since it doesn't exist
$(BINDIR):
	mkdir -p $(BINDIR)

%.cpp:
	$(error Missing source file required for building: $@)
	
# Clean up.
clean:
	rm -f $(BINDIR)/*
	rm -f *.o
	rm -f commands/*.o
	rm -f test/*.o
	rm -f fakes/*.o

# Automatically call clean.
.PHONY: clean
