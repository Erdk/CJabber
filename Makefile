CC=g++
CFLAGS=-g -I. -I/usr/include/ncursesw
LDFLAGS=-lgloox -lncursesw -pthread
OBJS=main.o xmppconnection.o printwin.o logsink.o program.o settings_handler.o popup.o textpopup.o
PROG=cjabber

all: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(PROG)

$(OBJS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJS) $(PROG)
