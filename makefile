CC := g++
TARGET := Ficland

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

$(OBJS): %.o:%.cpp
	echo OBJS: $(OBJS)
	$(CC) -c $(CFLAGS) $< -o $@
    
