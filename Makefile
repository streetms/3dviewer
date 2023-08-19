FLAGS	=-Wall -Wextra -Werror -std=c11 -g -O0
LIBS = -lcheck -lm

all : main

libmatrix.a :
	(! [ -d build ] && mkdir build) || (true)
	(! [ -d build/libs ] && mkdir build/libs) || (true)
	cd back/matrix && make s21_matrix.a && cp s21_matrix.a ../../build/libs/libmatrix.a

vector.o: back/vector.c
	(! [ -d build ] && mkdir build) || (true)
	(! [ -d build/obj ] && mkdir build/obj) || (true)
	gcc $(FLAGS) back/vector.c -c -o build/obj/vector.o

3D.o:  back/3D.c
	(! [ -d build ] && mkdir build) || (true)
	(! [ -d build/obj ] && mkdir build/obj) || (true)
	gcc $(FLAGS) back/3D.c -c -o build/obj/3D.o
test: back/main.c 3D.o libmatrix.a
	gcc back/main.c build/obj/3D.o build/libs/libmatrix.a -lm  -g -o build/test

main: lib3D.a libmatrix.a
	(! [ -d build ] && mkdir build) || (true)
	cd front && qmake && make


lib3D.a: 3D.o libmatrix.a vector.o
	(! [ -d build/libs ] && mkdir build/libs) || (true)
	ar rc lib3D.a build/obj/3D.o build/obj/vector.o build/libs/libmatrix.a
	ranlib lib3D.a
	mv lib3D.a build/libs/lib3D.a

clean :
	rm -rf build

