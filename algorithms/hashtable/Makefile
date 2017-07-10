CC		= gcc
CFLAGS		= -g -c -Wall 
LDFLAGS		= 
SOURCES		= test_hashtable.c hashtable.c
INCLUDES	= -I.
OBJECTS		= $(SOURCES:.c=.o)
TARGET		= test_hashtable

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
	./test_hashtable