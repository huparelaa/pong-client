compile:
	gcc -o client client.c protocole.c pong.c pong-src/drawers.c `sdl2-config --cflags --libs`