OS=$(shell uname)
LDFLAGS=-lpthread 
CFLAGS=-c -std=c99 -Wall
ifeq ($(OS),SunOS)
LDFLAGS=-mt -lpthread
CFLAGS=-c -std=c99 -mt 
endif
EXECUTABLE=task1
SOURCE=$(EXECUTABLE)_main.c
OBJECTS=$(SOURCE:.c=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) 

.c.o: $(SOURCE)
	$(CC) $(CFLAGS) $< -o $@ 
	
clean:
	rm -f $(OBJECTS)
