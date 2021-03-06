CC=g++
TARGET=imageops
LIB = LibImageOps
FLAGS=-std=c++11 -I $(LIB) -L $(LIB) -limageops

.PHONY: clean

$(TARGET): driver.o
	$(CC) -o $(TARGET) driver.o $(FLAGS)

driver.o: driver.cpp
	make -C $(LIB)
	$(CC) -c -o driver.o driver.cpp $(FLAGS)

tests: tests.cpp
	make -C $(LIB)
	$(CC) -o testRunner tests.cpp $(FLAGS)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./testRunner -s

clean:
	rm -f *.o ./$(TARGET) ./testRunner
	make -C $(LIB) clean

add: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./$(TARGET) -a shrek_rectangular.pgm donkey_mask.pgm output.pgm

subtract: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./$(TARGET) -s Lenna_standard.pgm Lenna_hat_mask.pgm output.pgm

invert: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./$(TARGET) -i shrek_rectangular.pgm output.pgm

mask: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./$(TARGET) -l shrek_rectangular.pgm donkey_mask.pgm output.pgm

threshold: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./$(TARGET) -t shrek_rectangular.pgm 250 output.pgm

filter: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./$(TARGET) -f Lenna_standard.pgm ./sample_filters/all_dir_edge_detect.fir output.pgm
