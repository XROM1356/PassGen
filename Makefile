.PHONY: all release clean

all: release

release: PassGen

hello: PassGen.cpp
	g++ -O2 PassGen.cpp -o PassGen

clean:
	rm -f PassGen

