TARGET = wsh
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

$(TARGET) :$(OBJS)
	gcc -o $(TARGET) $(OBJS)

clean :
	rm *.o $(TARGET)