FLAGS        =
CFLAGS       = -shared -fPIC -pedantic -Wall -Wextra

TARGET  = transbind.so
SOURCES = transbind.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) $(CFLAGS) -o $(TARGET) $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET)