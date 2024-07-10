CXX = g++
CXXFLAGS = -Wall -g

TARGET = nodo
SRCS = src/nodo.cpp src/funciones.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

reboot: clean all