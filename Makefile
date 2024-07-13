CFLAGS=-O2 -Wall
SRC=main.c interactive.c
HEADER=interactive.h
OUT=bfuck

$(OUT): $(SRC) $(HEADER)
	$(CC) $(SRC) $(CFLAGS) -o $(OUT)

