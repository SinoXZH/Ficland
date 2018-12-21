CC := g++

TARGET := Ficland

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

%.o : %.cpp
	$(CC) -c $< -o $@

clean :
	rm -f $(OBJS)
	rm -f $(TARGET)