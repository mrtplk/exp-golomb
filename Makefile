CC = g++

CFLAGS = -g -std=c++11 -Wall

TARGET = exp-golomb

all: $(TARGET)

$(TARGET): main.o BitStream.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o BitStream.o
	
main.o: main.cpp GolombEncoder.h GolombDecoder.h DataGenerator.h TxtLoader.h
	$(CC) $(CFLAGS) -c main.cpp


BitStream.o: BitStream.cpp BitStream.h
	$(CC) $(CFLAGS) -c BitStream.cpp

clean:
	-rm $(ODIR)/*.o $(objects) $(TARGET)
