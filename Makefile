obj-m += neo.o

PWD := $(shell pwd)
KDIR := /lib/modules/$(shell uname -r)/build

default:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean