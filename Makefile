project: project.o
	 gcc `pkg-config --cflags gtk+-3.0` project.o -o project `pkg-config --libs gtk+-3.0`
project.o: project.c project.h
	gcc `pkg-config --cflags gtk+-3.0` -Wall -c project.c `pkg-config --libs gtk+-3.0`
clean:
	rm *.o
	
