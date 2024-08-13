libstarline.so : starline.o build
	cc -shared -o build/libstarline.so build/starline.o

starline.o : starline.c starline.h build
	cc -c -Wall -fpic starline.c
	mv starline.o build/

build :
	mkdir build

clean :
	rm -rf build
