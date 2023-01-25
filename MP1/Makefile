.PHONY: clean all
CXX = g++

CFLAGS = -std=c++11 -Wall -Wextra -O3
SOURCE = $(wildcard *.cpp)
OUT = loser.o main.o md5.o

loser: $(OUT)
	$(CXX) $(CFLAGS) $(OUT) -o loser
	rm $(OUT)

loser.o:
	$(CXX) $(CFLAGS) -c loser.cpp -o loser.o

main.o:
	$(CXX) $(CFLAGS) -c main.cpp -o main.o

md5.o:
	$(CXX) $(CFLAGS) -c md5.cpp -o md5.o

clean:
	rm -rf loser