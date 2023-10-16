compile:
	gcc -o client client.c protocole.c parser.c pong_info_sender.c pong.c pong-src/drawers.c pong-src/ball.c pong-src/paddle.c pong-src/status_checkers.c `sdl2-config --cflags --libs`