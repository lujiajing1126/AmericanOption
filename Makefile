CC=g++

%.o: %.cc
	$(CC) -c -std=c++11  $^

AmericanOption: AmericanOption.o utils.o Matrix.o
	$(CC) -o $@ $^

clean:
	-rm *.o
	-rm AmericanOption

.PHONY:
	clean