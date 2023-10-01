compile: 
	gcc -o game app.c  drawers.c protocole.c `sdl2-config --cflags --libs`