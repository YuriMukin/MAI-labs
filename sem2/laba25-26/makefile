CC = cc
LD = cc
LDFLAGS = -o
CCFLAGS = -c
laba25_26: main.o list.o
	$(LD) $(LDFLAGS) laba25_26 main.o list.o
main.o: main.c list.h
	$(CC) $(CCFLAGS) main.c
list.o: list.c
	$(CC) $(CCFLAGS) list.c
	cc -o laba25_26 main.o list.o