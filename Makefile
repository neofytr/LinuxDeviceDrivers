obj-m = neo.o  # The obj-m variable is used by the kernel build system to specify modules to be built.
# The kernel build system automatically handles the compilation of .c files into .o files.
# To build a module, add its corresponding .c file to the obj-m variable using the .o extension.


PWD := $(shell pwd)
KDIR := /lib/modules/$(shell uname -r)/build

default:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean

transfer:
	multipass transfer -r ~/Desktop/LinuxDeviceDrivers/* primary:/home/ubuntu/Driver/