CFLAGS=-Wall
CXXFLAGS=-Wall
LDFLAGS=-Wall -L/opt/local/lib # needed for MacPorts. using environment vars (LD_LIBRARY_PATH) to show library location did not work :(
BOOST=-lboost_regex-mt # on MacPorts only multithreaded version is installed by default. could use autoconf to find a variant that exists on a system.

all: rtmpdump

clean:
	rm -f rtmpdump *.o

rtmpdump: log.o rtmp.o AMFObject.o rtmppacket.o rtmpdump.o
	g++ $(LDFLAGS) $^ -o $@ $(BOOST)

log.o: log.cpp log.h Makefile
rtmp.o: rtmp.cpp rtmp.h log.h AMFObject.h Makefile
AMFObject.o: AMFObject.cpp AMFObject.h log.h rtmp.h Makefile
rtmppacket.o: rtmppacket.cpp rtmppacket.h log.h Makefile
rtmpdump.o: rtmpdump.cpp rtmp.h log.h AMFObject.h Makefile

