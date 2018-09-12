CC=gcc
CFLAGS=-I. -I../lib/nanopb/
VPATH=../lib/nanopb
OBJS=var.o pb_common.o pb_encode.o pb_decode.o main.o
BINARY=mcu

%.pb.c: %.proto
	protoc $^ --nanopb_out=.

%.o: %.pb.c
	$(CC) -c -o $@ $^ $(CFLAGS)

%.o: %.c 
	$(CC) -c -o $@ $^ $(CFLAGS)

$(BINARY): $(OBJS) 
	$(CC) -o $@ $(OBJS) $(CFLAGS)

.PHONY: clean

clean: 
	rm -f *.o core *.pb.h *.pb.c $(BINARY)
