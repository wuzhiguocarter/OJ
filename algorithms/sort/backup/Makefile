CC		= gcc

CFLAGS		= -Wall -O3 -g -c  
INCLUDES	= -I.
LDFLAGS		= 

SOURCES		= $(wildcard *.c *.cpp)
OBJECTS		= $(patsubst %.c,%.o,${patsubst,%.cpp,%.o})
# OBJECTS		= $(SOURCES:.c=.o)
TARGET		= test_sort

all: $(SOURCES) $(TARGET) cleanOBJ run

$(TARGET): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

cleanOBJ:
	rm -rf $(OBJECTS)

clean:
	rm -rf $(TARGET)
run:
	./test_sort