.PHONY: all

all: beads

beads: beads.cpp
	g++ -o beads beads.cpp

.PHONY: run
run:
	./beads

.PHONY: clean
clean:
	-rm -f ./beads beads.out

.PHONY: debug
debug:
	g++ -g -o beads beads.cpp
	gdb beads