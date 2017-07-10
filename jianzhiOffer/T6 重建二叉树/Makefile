CC		= gcc
XX		= g++ -std=c++11

CFLAGS		= -Wall -O3 -g -c  
INCLUDES	= -I.
LDFLAGS		= 

SOURCES		= $(wildcard *.c *.cpp)
OBJECTS		= $(SOURCES:.c=.o)
# OBJECTS		= $(patsubst %.c,%.o,$(patsubst,%.cpp,%.o))

TARGET		= a.out

all: $(SOURCES) $(TARGET) 

 

$(TARGET): $(OBJECTS) 
	$(XX) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

.cpp.o:
	$(XX) $(CFLAGS) $(INCLUDES) $< -o $@

.PHONY: clean cleanall run
clean:
	rm -rf $(OBJECTS)

cleanall:
	rm -rf $(OBJECTS) $(TARGET)
run:
	./$(TARGET)