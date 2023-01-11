CC 	:= cc
CFLAGS 	:= -g -Wall -Wextra 
TARGET	:= sh1
all: sh1.c
	$(CC) $(CFLAGS) $^ -o $(TARGET)
.PHONY:
clean:
	$(RM) -drvf $(TARGET)
