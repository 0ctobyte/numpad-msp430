CC=msp430-gcc
CFLAGS=-Os -Wall -g -std=c99 -mmcu=msp430g2553
PROGRAM=numpad
OBJS=$(PROGRAM).o


all: $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGRAM).elf $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -fr $(PROGRAM).elf $(OBJS)
