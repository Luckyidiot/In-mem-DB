COMPILER = gcc

PYTHON_FLAGS = $(python3-config --cflags)
PYTHON_LINKS = $(python3-config --ldflags --embed)

EXTERNAL_LIBS =
SERVER_SRC = server.c utils.c kernel.c
EXE = server

all: $(EXE)
	
server: $(SERVER_SRC) $(SERVER_WITHPY)
	#gcc -Wall $(PYTHON_FLAGS) $(SERVER_WITHPY) $(PYTHON_LINKS) $(SERVER_SRC) -o $@
	gcc -Wall $(SERVER_SRC) -o $@