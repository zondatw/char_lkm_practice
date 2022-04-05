CC = gcc
obj-m+=charlkm.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) client.c -o client
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm client