COMPILER = gcc

EXTERNAL_LIBS =
SERVER_SRC = utils.c kernel.c main.c
EXE = fam

all: $(EXE)
	
fam: $(SERVER_SRC) $(SERVER_WITHPY)
	gcc -g -Wall $(SERVER_SRC) -o $@