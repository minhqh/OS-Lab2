CC = gcc
CFLAGS = -Wall -Wextra -O2

SERIAL = sum_serial
MULTI = sum_multi-thread

all: $(SERIAL) $(MULTI)

$(SERIAL): sum_serial.c
	$(CC) $(CFLAGS) -o $(SERIAL) sum_serial.c

$(MULTI): sum_multi-thread.c
	$(CC) $(CFLAGS) -pthread -o $(MULTI) sum_multi-thread.c

# Xóa file build
clean:
	rm -f $(SERIAL) $(MULTI)