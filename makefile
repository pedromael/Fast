CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = src/main.c src/tokenizer.c src/parser.c src/runtine.c src/error.c
HEADERS = header/index.h
TARGET = cfast

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
