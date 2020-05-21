CXX = g++

CLIB = -lcurl -ljsoncpp -lpthread

SCR = ../TulingNLP/

OBJS = main.cpp \
	baidu_deploy.cpp \
	debug_log.cpp


INCLUDE = -I./include
TARGET = product

$(TARGET) : $(OBJS)
	$(CXX) $(INCLUDE) $(OBJS) -o $(TARGET) $(CLIB) 
	
all: $(TARGET)

clean:
	rm -rf $(TARGET)
