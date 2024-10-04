COMPILER = gcc

PYTHON_FLAGS = $(python3-config --cflags)
PYTHON_LINKS = $(python3-config --ldflags --embed)

EXTERNAL_LIBS =
SERVER_SRC = utils.c kernel.c server.c
EXE = server

all: $(EXE)
	
server: $(SERVER_SRC) $(SERVER_WITHPY)
	gcc -g -Wall $(SERVER_SRC) -o $@