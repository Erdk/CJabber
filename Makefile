CC=g++
CFLAGS=-g -I/usr/include/ncursesw
LDFLAGS=-lgloox -lncursesw -pthread
OBJS=main.o xmppconnection.o printwin.o logsink.o

all: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o last_chance

main.o: main.cpp printwin.cpp xmppconnection.cpp logsink.cpp
	$(CC) $(CFLAGS) -c main.cpp

xmppconnection.o: xmppconnection.cpp printwin.cpp logsink.cpp
	$(CC) $(CFLAGS) -c xmppconnection.cpp

printwin.o: printwin.cpp
	$(CC) $(CFLAGS) -c printwin.cpp

logsink.o: logsink.cpp
	$(CC) $(CFLAGS) -c logsink.cpp

.PHONY: clean

clean:
	rm -f $(OBJS) last_chance
