CC=g++
CFLAGS=-g -I. -I/usr/include/ncursesw
LDFLAGS=-lgloox -lncursesw -pthread
OBJS=main.o xmppconnection.o printwin.o logsink.o program.o settings_handler.o popup.o textpopup.o
PROG=cjabber

all: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(PROG)

# main.o: main.cpp printwin.cpp xmppconnection.cpp logsink.cpp program.cpp settings_handler.cpp popup.cpp
# 	$(CC) $(CFLAGS) -c main.cpp
#
# xmppconnection.o: xmppconnection.cpp printwin.cpp logsink.cpp
# 	$(CC) $(CFLAGS) -c xmppconnection.cpp
#
# printwin.o: printwin.cpp
# 	$(CC) $(CFLAGS) -c printwin.cpp
#
# logsink.o: logsink.cpp
# 	$(CC) $(CFLAGS) -c logsink.cpp
#
# program.o: program.cpp xmppconnection.cpp printwin.cpp popup.cpp
# 	$(CC) $(CFLAGS) -c program.cpp
#
# settings_handler.o: settings_handler.cpp
# 	$(CC) $(CFLAGS) -c settings_handler.cpp
#
# popup.o: popup.cpp
# 	$(CC) $(CFLAGS) -c popup.cpp

$(OBJS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJS) $(PROG)
