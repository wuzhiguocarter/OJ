.PHONY: all
all: test_dclist clean run

test_dclist: test_dclist.c dclist.c
	gcc -std=c99 -o test_dclist test_dclist.c dclist.c

libdclist.so: dclist.c
	gcc -std=c99 -fPIC -shared dclist.c -o libdclist.so

clean:
	-rm -f *.o

run:
	./test_dclist