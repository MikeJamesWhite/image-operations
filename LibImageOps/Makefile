CC=g++
TARGET=libimageops.so
FLAGS=-fPIC -shared -std=c++11

$(TARGET): Image.o
	$(CC) -o $(TARGET) Image.o $(FLAGS)

Image.o: Image.cpp Image.h
	$(CC) -c -o Image.o Image.cpp $(FLAGS)

clean:
	rm -f *.o *.so