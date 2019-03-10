CC := g++

TARGET := ../bin/Ficland

CFLAG :=

ifeq ($(MODE),debug)
CFLAG += -DDEBUG
endif

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

%.o : %.cpp
	$(CC) -c $(CFLAG) $< -o $@

clean :
	rm -f $(OBJS)
	rm -f $(TARGET)