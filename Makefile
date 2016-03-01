CFLAGS = -g -Wall -I./

all: test

test: example.exe
	@./example.exe

example.exe: example.o mocha.o
	$(CC) $(CFLAGS) -o $@ example.o mocha.o

clean:
	rm -rf *.o *.exe
