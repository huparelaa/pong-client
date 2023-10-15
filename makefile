compile:
	gcc -o client client.c protocole.c parser.c pong.c pong-src/drawers.c pong-src/ball.c pong-src/paddle.c `sdl2-config --cflags --libs`