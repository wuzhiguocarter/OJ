CC			= gcc
CFLAGS		= -c -Wall
# LDFLAGS		= -pthread #-lpthread
SOURCES		= UnitTest_LRUCache.c LRUCache.c LRUCacheADT.c
INCLUDES	= -I.
OBJECTS		= $(SOURCES:.c=.o)
TARGET		= UnitTest_LRUCache

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJECTS) #$(TARGET)
