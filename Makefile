try: try.c
	gcc `pkg-config --cflags gtk+-3.0` -o try try.c `pkg-config --libs gtk+-3.0` 
