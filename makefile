# 编译器和编译选项
CC = mpicc
CFLAGS = -Wall

# 目标文件
TARGET = bcast_test

# 源文件
SOURCES = main.c functions.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)