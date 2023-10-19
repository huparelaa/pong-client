# Nombre del archivo Makefile

# Variables del Makefile
CC = gcc
CFLAGS = -Wall -Wextra -pedantic
SOURCES = client.c protocole.c parser.c pong_info_sender.c pong.c pong-src/drawers.c pong-src/ball.c pong-src/paddle.c pong-src/status_checkers.c
EXECUTABLE = client

# Regla para compilar el programa
compile: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) -o $(EXECUTABLE) $(SOURCES) `sdl2-config --cflags --libs`

# Regla para instalar SDL en un sistema Linux (basado en apt-get)
install_sdl:
	sudo apt-get update
	sudo apt-get install libsdl2-dev

# Regla para compilar y ejecutar el programa
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Regla para limpiar los archivos generados
clean:
	rm -f $(EXECUTABLE)

.PHONY: compile install_sdl run clean
