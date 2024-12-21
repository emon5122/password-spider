CC = gcc
CFLAGS = -Wall
OBJ = main.o password_spider.o
OUT = password_spider

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT)

main.o: main.c password_spider.h
	$(CC) $(CFLAGS) -c main.c

password_spider.o: password_spider.c password_spider.h
	$(CC) $(CFLAGS) -c password_spider.c

clean:
	rm -f $(OBJ) $(OUT)
